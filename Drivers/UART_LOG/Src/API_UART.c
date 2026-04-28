/**
 API_UART.c
 Ismael Farid Marquez Quila
  Implementación de la API de comunicación serie (Telemetría).

 */

#include "API_UART.h"
#include "UART_port.h"
#include <stdio.h>
#include <string.h>

/**
 Inicializa el periférico de comunicación serie.
 */
void API_UART_Init(void) {
    /* Delegamos la configuración de baudios y paridad a la capa de puerto
       para mantener la aplicación agnóstica a la configuración física. */
    UART_Port_Init();
}

/**
  Transmisión de cadenas de texto genéricas.
 param str Puntero al string (null-terminated).
 Se valida que el puntero no sea NULL antes de operar
 para evitar fallos de segmentación o accesos a memoria no permitidos.
 */
void API_UART_SendString(char *str) {
    if (str != NULL) {
        /* Se calcula la longitud dinámicamente para optimizar el tiempo
           de ocupación del bus en la capa de puerto. */
        UART_Port_Transmit((uint8_t*)str, (uint16_t)strlen(str));
    }
}

/**
 Formatea y envía los datos de estabilidad (Pitch/Roll).
 Se utiliza un buffer local de 64 bytes, tamaño suficiente
 para la trama de telemetría sin comprometer excesivamente el stack.
 El formato CSV con dos decimales (%.2f) es el estándar elegido para facilitar
 el post-procesamiento de los datos de la canoa en herramientas externas.
 */
void API_UART_LogStability(float pitch, float roll) {
    char buffer[64];

    /* El uso de sprintf asegura un formato de trama determinista, vital
       para la sincronización con el software de monitoreo en PC. */
    int len = sprintf(buffer, "DATA: PITCH:%.2f, ROLL:%.2f\r\n", pitch, roll);

    if (len > 0) {
        UART_Port_Transmit((uint8_t*)buffer, (uint16_t)len);
    }
}
