#include "Delay_port.h"
#include "stm32f4xx_hal.h"

void Delay_Port_Init(void) {
    // El SysTick ya se inicia solo en el HAL_Init
}

uint32_t Delay_Port_GetTick(void) {
    return HAL_GetTick(); // Esta es la lámpara que enciende el interruptor
}
