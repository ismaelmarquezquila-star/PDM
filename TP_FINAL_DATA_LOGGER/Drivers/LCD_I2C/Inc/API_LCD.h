#ifndef API_LCD_H_
#define API_LCD_H_

#include <stdint.h>
#include <stdio.h>
/* Funciones que la aplicación Canoa utiliza para mostrar datos */
void API_LCD_Init(void);
void API_LCD_SendString(char *str);
void API_LCD_PutCur(int row, int col);
void API_LCD_Clear(void);
void API_LCD_WriteCleanLine(uint8_t row, char* message);
#endif /* API_LCD_H_ */
