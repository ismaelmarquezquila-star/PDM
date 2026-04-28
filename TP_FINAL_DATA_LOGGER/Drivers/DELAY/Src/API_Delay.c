/**
 API_Delay.c
 Ismael Farid Marquez Quila
 Implementación de la API de tiempos no bloqueantes.

 */

#include "API_Delay.h"
#include "stm32f4xx_hal.h"
#include <stddef.h>

void API_Delay_Init(void) {
    /* La inicialización es agnóstica al hardware; el tick ya es gestionado
       por el HAL_Init del sistema principal. */
}

void API_Delay_Wait(uint32_t ms) {
    /* Encapsulamiento de la función bloqueante para uso exclusivo en Init */
    HAL_Delay(ms);
}

void API_Delay_Config(delay_t * delay, tick_t duration) {
    /* Se inicializa la estructura con running en false
       para permitir que el cronómetro se dispare solo cuando sea consultado
       por primera vez optimizando el inicio de la MEF. */
    if (delay != NULL) {
        delay->duration = duration;
        delay->running = false;
    }
}

/**
Lógica central del retardo no bloqueante.
 Se utiliza la resta de ticks actuales menos el
 tiempo de inicio. Esto garantiza que el sistema funcione correctamente
 incluso cuando el contador HAL_GetTick sufra un desbordamiento (overflow).
 */
bool_t API_Delay_IsDone(delay_t * delay) {
    if (delay == NULL) return false;

    /* Inicio automático del cronómetro en la primera consulta */
    if (!delay->running) {
        delay->startTime = HAL_GetTick();
        delay->running = true;
        return false;
    }

    /* Verificación del tiempo transcurrido sin bloquear el procesador */
    if ((HAL_GetTick() - delay->startTime) >= delay->duration) {

        /* REINICIO AUTOMÁTICO: Se resetea el tiempo de inicio para permitir
           eventos periódicos (como el parpadeo del LED) sin reconfiguración manual. */
        delay->startTime = HAL_GetTick();
        return true;
    }
    return false;
}
