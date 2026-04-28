#include "SD_port.h"
#include "spi.h"
#include "main.h"
#include "API_UART.h"
/* FUNCIONES PRIVADAS DE BAJO NIVEL */

static void CS_Select(void) {
    HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
}

static void CS_Deselect(void) {
    HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
}

static uint8_t SPI_TransmitReceive(uint8_t data) {
    uint8_t rx_data = 0xFF;
    // Bajamos el timeout a 10ms para que si no hay SD, el código siga y la terminal hable
    if (HAL_SPI_TransmitReceive(&hspi1, &data, &rx_data, 1, 10) != HAL_OK) {
        return 0xFF;
    }
    return rx_data;
}

static uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg) {
    uint8_t res, n;

    // La SD requiere que se mande un byte de sincronización antes de bajar CS
    SPI_TransmitReceive(0xFF);
    CS_Select();

    SPI_TransmitReceive(0x40 | cmd);
    SPI_TransmitReceive((uint8_t)(arg >> 24));
    SPI_TransmitReceive((uint8_t)(arg >> 16));
    SPI_TransmitReceive((uint8_t)(arg >> 8));
    SPI_TransmitReceive((uint8_t)arg);

    n = 0x01;
    if (cmd == 0) n = 0x95; // CRC para CMD0
    if (cmd == 8) n = 0x87; // CRC para CMD8
    SPI_TransmitReceive(n);

    n = 10;
    do {
        res = SPI_TransmitReceive(0xFF);
    } while ((res & 0x80) && --n);

    // No liberamos CS aquí porque algunas funciones de lectura necesitan el bus tomado
    return res;
}

static int SD_ReadSector(uint32_t sector, uint8_t *buff) {
    uint8_t res;
    uint16_t i;

    res = SD_SendCmd(17, sector);
    if (res != 0x00) {
        CS_Deselect();
        return 1;
    }

    i = 1000;
    do {
        res = SPI_TransmitReceive(0xFF);
    } while (res != 0xFE && --i);

    if (res != 0xFE) {
        CS_Deselect();
        return 1;
    }

    for (i = 0; i < 512; i++) buff[i] = SPI_TransmitReceive(0xFF);

    SPI_TransmitReceive(0xFF); // CRC
    SPI_TransmitReceive(0xFF);

    CS_Deselect();
    SPI_TransmitReceive(0xFF);
    return 0;
}

/* FUNCIONES PÚBLICAS REQUERIDAS POR FATFS */

DSTATUS SD_disk_initialize(BYTE pdrv) {
    uint8_t res;
    uint16_t i;

    // 1. Iniciar a velocidad muy baja para compatibilidad (< 400kHz)
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) return STA_NOINIT;

    // 2. Sincronización inicial: CS en alto y mandar 80 pulsos de reloj
    CS_Deselect();
    HAL_Delay(10);
    for (i = 0; i < 10; i++) SPI_TransmitReceive(0xFF);

    // 3. CMD0: Resetear la tarjeta a modo Idle
    API_UART_SendString("SD: Enviando CMD0...\r\n");
    res = SD_SendCmd(0, 0);
    CS_Deselect();
    if (res != 0x01) {
        API_UART_SendString("Error: SD no responde CMD0 (revisar cables/voltaje)\r\n");
        return STA_NOINIT;
    }

    // 4. CMD8: Verificar voltaje (Indispensable para SDHC/SDXC)
    API_UART_SendString("SD: CMD0 OK. Enviando CMD8...\r\n");
    res = SD_SendCmd(8, 0x1AA);
    if (res == 0x01) {
        // Leer los 4 bytes de respuesta R7
        for (i = 0; i < 4; i++) SPI_TransmitReceive(0xFF);
    }
    CS_Deselect();

    // 5. ACMD41: Inicializar la tarjeta (Sacarla de Idle)
    API_UART_SendString("SD: Intentando ACMD41 (Iniciando tarjeta)...\r\n");
    i = 2000; // Aumentamos reintentos por si la SD es lenta
    do {
        SD_SendCmd(55, 0);                 // Prefijo para comandos específicos
        res = SD_SendCmd(41, 0x40000000);  // ACMD41 con soporte de alta capacidad
        CS_Deselect();
        HAL_Delay(1); // Pequeña espera entre intentos
    } while (res != 0x00 && --i);

    if (res != 0x00) {
        API_UART_SendString("Error: Tiempo agotado en ACMD41. SD no lista.\r\n");
        return STA_NOINIT;
    }

    // 6. Subir velocidad para operación normal (Lectura/Escritura rápida)
    // El prescaler 8 o 16 suele ser el punto dulce entre velocidad y estabilidad
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    HAL_SPI_Init(&hspi1);

    API_UART_SendString("SD: ¡INICIALIZACION EXITOSA!\r\n");
    return 0;
}
DSTATUS SD_disk_status(BYTE pdrv) {
    return 0;
}

DRESULT SD_disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count) {
    if (pdrv) return RES_PARERR;
    for (; count > 0; count--) {
        if (SD_ReadSector(sector, buff) != 0) return RES_ERROR;
        sector++;
        buff += 512;
    }
    return RES_OK;
}

/* IMPORTANTE: Implementamos la escritura para que no falle al intentar crear el LOG */
DRESULT SD_disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count) {
    if (pdrv) return RES_PARERR;
    uint8_t res;

    for (; count > 0; count--) {
        res = SD_SendCmd(24, sector); // CMD24 = Write Block
        if (res == 0x00) {
            SPI_TransmitReceive(0xFF);
            SPI_TransmitReceive(0xFE); // Token de inicio
            for (int i = 0; i < 512; i++) SPI_TransmitReceive(buff[i]);
            SPI_TransmitReceive(0xFF); // CRC
            SPI_TransmitReceive(0xFF);

            if ((SPI_TransmitReceive(0xFF) & 0x1F) != 0x05) return RES_ERROR;
            while (SPI_TransmitReceive(0xFF) == 0); // Esperar que termine de escribir
        }
        CS_Deselect();
        sector++;
        buff += 512;
    }
    return RES_OK;
}

DRESULT SD_disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    switch (cmd) {
        case CTRL_SYNC: return RES_OK;
        case GET_SECTOR_COUNT: return RES_OK;
        case GET_SECTOR_SIZE: *(WORD*)buff = 512; return RES_OK;
        case GET_BLOCK_SIZE: *(DWORD*)buff = 1; return RES_OK;
    }
    return RES_PARERR;
}
