#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdint.h>
#include <stdbool.h>

/* Tipo de dato booleano para el proyecto */
typedef bool bool_t;

/* Prototipos de funciones públicas [cite: 121, 122, 123, 124] */
bool_t uartInit();
void uartSendString(uint8_t* pstring);
void uartSendStringSize(uint8_t* pstring, uint16_t size);
void uartReceiveStringSize(uint8_t* pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
