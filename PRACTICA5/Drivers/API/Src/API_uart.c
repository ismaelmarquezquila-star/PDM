#include "API_uart.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Configuración privada */
#define UART_TIMEOUT 100
extern UART_HandleTypeDef huart2;

/* Implementación de uartInit */
bool_t uartInit() {
    /* Verificamos que la UART esté configurada */
    if (HAL_UART_GetState(&huart2) == HAL_UART_STATE_RESET) {
        return false;
    }

    char msg[100];
    sprintf(msg, "\r\n--- UART Inicializada ---\r\nBaudrate: %lu\r\n8N1\r\n\r\n", huart2.Init.BaudRate);
    uartSendString((uint8_t*)msg);

    return true;
}

/* Envía string completo hasta encontrar '\0' */
void uartSendString(uint8_t* pstring) {
    if (pstring == NULL) {
        return;
    }
    uint16_t size = (uint16_t)strlen((char*)pstring);
    HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT);
}

/* Envía una cantidad específica de caracteres */
void uartSendStringSize(uint8_t* pstring, uint16_t size) {
    if (pstring == NULL || size < 1 || size > 256) {
        return;
    }
    HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT);
}

/* Recibe datos en modo polling */
void uartReceiveStringSize(uint8_t* pstring, uint16_t size) {
    if (pstring == NULL || size < 1 || size > 256) {
        return;
    }
    HAL_UART_Receive(&huart2, pstring, size, UART_TIMEOUT);
}
