#ifndef API_DELAY_H_
#define API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>

/* Tipo de dato para booleanos (CESE style) */
typedef bool bool_t;
typedef uint32_t tick_t;

/* ESTRUCTURA CLAVE: El cronómetro para que no se bloquee el micro */
typedef struct {
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void API_Delay_Init(void);
void API_Delay_Wait(uint32_t ms);

/* FUNCIONES PARA LA MEF (No bloqueantes) */
void API_Delay_Config(delay_t * delay, tick_t duration); // Escribe el tiempo
bool_t API_Delay_IsDone(delay_t * delay);                // Lee si ya pasó el tiempo

#endif /* API_DELAY_H_ */
