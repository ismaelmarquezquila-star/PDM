#include "API_delay.h"
#include "main.h" /* Para HAL_GetTick() */
#include <stddef.h>

void delayInit(delay_t * delay, tick_t duration) {
    if (delay == NULL) return;
    delay->duration = duration;
    delay->running = false;
}

bool_t delayRead(delay_t * delay) {
    if (delay == NULL) return false;

    if (!delay->running) {
        delay->startTime = HAL_GetTick();
        delay->running = true;
        return false;
    }

    if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
        delay->running = false;
        return true;
    }
    return false;
}

void delayWrite(delay_t * delay, tick_t duration) {
    if (delay != NULL) {
        delay->duration = duration;
    }
}
