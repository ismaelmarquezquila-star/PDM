#ifndef LCD_PORT_H_
#define LCD_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/* Tipo de dato requerido para uniformidad en la CESE */
typedef bool bool_t;

/* Prototipos de funciones de bajo nivel (Capa 2 OSI) */
bool_t LCD_Port_I2C_Transmit(uint16_t devAddr, uint8_t *pData, uint16_t size);
void LCD_Port_Delay(uint32_t ms);

#endif /* LCD_PORT_H_ */
