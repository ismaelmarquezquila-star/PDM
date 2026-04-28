/**
 API_Delay_Port.h
 author Ismael Farid Marquez Quila
 Interfaz de bajo nivel para la gestión de tiempos.
Este archivo actúa como el "Port" específico para la placa Nucleo-F446RE.
 Su existencia permite que la lógica de la MEF no dependa directamente
de las bibliotecas de STMicroelectronics (HAL), facilitando la portabilidad.
 */

#ifndef API_DELAY_PORT_H_
#define API_DELAY_PORT_H_

#include <stdint.h>

/**
 rief Wrapper de bajo nivel para retardos de hardware.
 Se encapsula la función HAL_Delay en este puerto para que
 si el proyecto se migra a otra arquitectura (ej. NXP o ESP32), solo sea
 necesario modificar este archivo sin alterar la API genérica de la aplicación.
 param ms Cantidad de milisegundos de espera.
 */
void Port_Delay_ms(uint32_t ms);

#endif /* API_DELAY_PORT_H_ */
