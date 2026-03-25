
#include "API_delay.h"
#include "main.h"

/* delayInit: Configura un delay no bloqueante, dejándolo listo para usarse
delay_t *delay: estructura donde se guardará la información del delay
tick_t duration: tiempo que durará el delay
no devuelve ningún valor
 */
void delayInit( delay_t * delay, tick_t duration)
{
	if(delay == NULL && duration != 0)
	{
		Error_Handler();
	}

	delay->duration = duration;
	delay->running = false;
}

/* delayRead: Verifica el tiempo transcurrido y comprueba si el delay ya terminó
Parámetros:
delay_t *delay: estructura que contiene la información del delay
Retorna:
true: cuando el tiempo del delay ya se cumplió
false: cuando el delay aún sigue en curso
 */
bool_t delayRead(delay_t* delay)
{
	if(delay == NULL)
	{
		Error_Handler();
	}

	if(!delay->running)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		if((HAL_GetTick() - delay->startTime) >= delay->duration)
		{
			delay->running = false;
			return true;
		}
	}
	return false;
}

/* delayWrite: Actualiza el tiempo del delay con un nuevo valor */
void delayWrite(delay_t* delay, tick_t duration)
{
	if(delay == NULL)
	{
		Error_Handler();
	}

	delay->duration = duration;
}

/* delayWrite: Indica si el delay está corriendo o detenido */

bool_t  delayIsRunning(delay_t *delay)
{
	if(delay == NULL)
	{
		Error_Handler();
	}

	return delay->running;
}
