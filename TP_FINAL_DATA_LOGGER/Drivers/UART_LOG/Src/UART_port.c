#include "UART_port.h"
#include "usart.h"
#include <stddef.h> // Para NULL

bool_t UART_Port_Init(void) {
    return true;
}

bool_t UART_Port_Transmit(uint8_t *pData, uint16_t size) {
    if (pData != NULL && size > 0) {
        // el timeout a 10ms para que no trabe el resto del código
        if (HAL_UART_Transmit(&huart2, pData, size, 10) == HAL_OK) {
            return true;
        }
    }
    return false;
}
