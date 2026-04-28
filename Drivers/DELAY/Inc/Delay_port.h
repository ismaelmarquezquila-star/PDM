#ifndef DELAY_PORT_H_
#define DELAY_PORT_H_

#include <stdint.h>

/* Definición de tipo de dato para el tiempo del sistema */
typedef uint32_t tick_t;

/* Prototipos de funciones de bajo nivel */
void Delay_Port_Init(void);
tick_t Delay_Port_GetTick(void);

#endif /* DELAY_PORT_H_ */
