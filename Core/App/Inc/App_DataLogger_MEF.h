/* USER CODE BEGIN Header */
/**

  App_DataLogger_MEF.h
  Interfaz de la Máquina de Estados Finitos (MEF)
  author: Ismael Farid Marquez Quila
   Este archivo define los puntos de entrada para la lógica de
  aplicación del Datalogger. Se diseñó siguiendo un esquema
  de capas para desacoplar la MEF del hardware específico.

  */
/* USER CODE END Header */


#ifndef APP_DATALOGGER_MEF_H_
#define APP_DATALOGGER_MEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 No se incluyen drivers de periféricos (I2C, SPI, etc.) en este header para
 respetar la jerarquía de capas. El main.c solo necesita conocer las funciones
 de alto nivel de la aplicación, manteniendo el hardware encapsulado.
 */

/* Prototipos de funciones exportadas ---------------------------------------------*/

/**
Inicialización del sistema de control.
 Configura el estado inicial de la MEF y lanza la secuencia de arranque de
 los servicios (UART, LCD, etc.).
 @note Se debe invocar una única vez en el main.c antes del bucle infinito.
 */
void App_DataLogger_Init(void);

/**
 * @brief Función de despacho (scheduler) de la MEF.
 Ejecuta las transiciones de estado basándose en eventos de tiempo no bloqueantes
 y entradas de usuario. Es el corazón del sistema de monitoreo de la canoa.
 Para garantizar el determinismo del sistema, esta función no debe
  contener llamadas bloqueantes prolongadas.
 */
void App_DataLogger_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_DATALOGGER_MEF_H_ */
