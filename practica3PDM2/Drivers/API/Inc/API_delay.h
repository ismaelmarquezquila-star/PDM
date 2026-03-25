

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/*
Inclusion de librerias o biblioteca
 */
#include <stdint.h>
#include <stdbool.h>
/*
Tipos de datos
 */
typedef uint32_t tick_t;
typedef bool bool_t;
/*
Estructura que contiene el tiempo de inicio, duracion y ejecucion
 */
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
/*
Funciones de Inicializacion de variables, escritura, lectura y comprovacion de ejecucion running
 */
void 	delayInit(delay_t * delay, tick_t duration);
void 	delayWrite(delay_t * delay, tick_t duration);
bool_t 	delayRead(delay_t * delay);
bool_t  delayIsRunning(delay_t *delay);

#endif /* API_INC_API_DELAY_H_ */
