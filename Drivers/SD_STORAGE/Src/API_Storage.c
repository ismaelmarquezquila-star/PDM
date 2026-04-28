/**
 * @file API_Storage.c
 * @author Ismael Farid Marquez Quila
 * @brief Capa de aplicación para la persistencia de datos en tarjeta SD.
 * @details Provee una interfaz simplificada sobre FatFS para la gestión de
 * logs del Datalogger, asegurando la integridad de la escritura.
 */

#include "API_Storage.h"
#include "ff.h"
#include <stdio.h>

extern char USERPath[4];
extern FATFS USERFatFS;
static FIL fil;
static bool_t is_mounted = false;

/**
 Inicializa y monta la unidad de almacenamiento.
 return true si el montaje fue exitoso.
 Se utiliza el parámetro de montaje inmediato (1) para
 validar la presencia física de la SD y la integridad del sistema de archivos
 antes de iniciar la operación del sistema.
 */
bool_t API_Storage_Init(void) {
    HAL_Delay(100);
    FRESULT res = f_mount(&USERFatFS, (TCHAR const*)USERPath, 1);

    if (res == FR_OK) {
        is_mounted = true;
        return true;
    }

    is_mounted = false;
    return false;
}

/**
 Abre un archivo para escritura.
 Se utiliza el modo FA_OPEN_APPEND porque garantiza que los nuevos
 datos se añadan al final del archivo sin sobrescribir registros anteriores.
 */
bool_t API_Storage_OpenFile(const char* filename) {
    if (!is_mounted) return false;
    return (f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE) == FR_OK);
}

/**
  Registra los datos de estabilidad en formato CSV.
 Se verifica que la cantidad de bytes escritos (bw)
 coincida con la longitud del buffer para detectar errores de sector o memoria llena.
 */
bool_t API_Storage_LogData(BoatStatus_t data) {
    UINT bw;
    char buffer[64];
    int len = sprintf(buffer, "%.2f, %.2f\r\n", data.pitch, data.roll);
    if (f_write(&fil, buffer, len, &bw) == FR_OK) {
        return (bw == len);
    }
    return false;
}


bool_t API_Storage_CloseFile(void) {
    return (f_close(&fil) == FR_OK);
}
