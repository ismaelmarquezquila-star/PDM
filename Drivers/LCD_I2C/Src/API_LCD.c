/**
 API_LCD.c
 Ismael Farid Marquez Quila
 Driver genérico para pantalla LCD 1602 vía expansor I2C.
 Implementa el protocolo de 4 bits sobre I2C, delegando el transporte
 a la capa de puerto para asegurar la portabilidad del sistema.
 */

#include "API_LCD.h"
#include "LCD_port.h"

/* Dirección esclavo por defecto para el expansor PCF8574 */
#define LCD_ADDR 0x4E

/**
 Escribe una línea completa asegurando la limpieza de caracteres previos.
 Se utiliza un padding de espacios (%-16s) en lugar
 de limpiar la pantalla (Clear) para evitar el parpadeo visual (flicker) y
 reducir el tiempo de ocupación del bus I2C.
 */
void API_LCD_WriteCleanLine(uint8_t row, char* message) {
    char buffer[17];
    snprintf(buffer, sizeof(buffer), "%-16s", message);
    API_LCD_PutCur(row, 0);
    API_LCD_SendString(buffer);
}

/**
 * @brief Envío de comandos al controlador HD44780.
 * @details Se fragmenta el comando en nibbles (alto y bajo) siguiendo el
 * esquema de 4 bits requerido por el expansor I2C.
 */
void API_LCD_SendCmd(char cmd) {
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);

    /* Empaquetado con flancos de habilitación (EN) y RS en bajo (comando) */
    data_t[0] = data_u | 0x0C;
    data_t[1] = data_u | 0x08;
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;

    LCD_Port_I2C_Transmit(LCD_ADDR, data_t, 4);
}

void API_LCD_SendData(char data) {
    uint8_t data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);

    /* RS en alto para indicar envío de datos al registro de memoria */
    data_t[0] = data_u | 0x0D;
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;

    LCD_Port_I2C_Transmit(LCD_ADDR, data_t, 4);
}

void API_LCD_Init(void) {
    /* Secuencia de inicialización según datasheet para modo 4 bits */
    LCD_Port_Delay(50);
    API_LCD_SendCmd(0x30);
    LCD_Port_Delay(5);
    API_LCD_SendCmd(0x30);
    LCD_Port_Delay(1);
    API_LCD_SendCmd(0x32);
    LCD_Port_Delay(10);

    API_LCD_SendCmd(0x28); // 2 líneas, matriz 5x8
    API_LCD_SendCmd(0x0C); // Display ON, Cursor OFF
    API_LCD_SendCmd(0x01); // Reset de DDRAM
    LCD_Port_Delay(2);
}

void API_LCD_SendString(char *str) {
    while (*str) API_LCD_SendData(*str++);
}

void API_LCD_Clear(void) {
    API_LCD_SendCmd(0x01);
    LCD_Port_Delay(2);
}

/**
 Posicionamiento del cursor en la memoria DDRAM.
 row Índice de fila (0-1).
 param col Índice de columna (0-15).
 */
void API_LCD_PutCur(int row, int col) {
    /* Cálculo de dirección basado en los offsets estándar (0x80 y 0xC0) */
    switch (row) {
        case 0: col |= 0x80; break;
        case 1: col |= 0xC0; break;
    }
    API_LCD_SendCmd(col);
}
