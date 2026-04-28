#ifndef UART_PORT_H_
#define UART_PORT_H_

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

bool_t UART_Port_Init(void);
bool_t UART_Port_Transmit(uint8_t *pData, uint16_t size);

#endif
