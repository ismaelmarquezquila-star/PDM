#include "main.h" // Aquí vive HAL_Delay

void Port_Delay_ms(uint32_t ms) {
	/* Llamada directa al servicio de tiempo del microcontrolador específico */
    HAL_Delay(ms);
}
