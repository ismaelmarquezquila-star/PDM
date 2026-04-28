#ifndef API_UART_H_
#define API_UART_H_

#include <stdint.h>

void API_UART_Init(void);
void API_UART_SendString(char *str);
void API_UART_LogStability(float pitch, float roll);

#endif
