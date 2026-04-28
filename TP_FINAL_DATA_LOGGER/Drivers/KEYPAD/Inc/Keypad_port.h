#ifndef KEYPAD_PORT_H_
#define KEYPAD_PORT_H_

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

/* Prototipos de bajo nivel para el teclado matricial */
void Keypad_Port_Init(void);
void Keypad_Port_WriteRow(uint8_t row, bool_t state);
bool_t Keypad_Port_ReadCol(uint8_t col);
void Keypad_Port_Delay(uint32_t ms);

#endif /* KEYPAD_PORT_H_ */
