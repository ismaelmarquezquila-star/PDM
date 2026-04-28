/**
 API_GPIO_Port.h
 author Ismael Farid Marquez Quila
 brief Interfaz del puerto de entrada/salida para periféricos GPIO.
 details Este módulo define las funciones de bajo nivel específicas de hardware
 para el teclado matricial y el indicador visual. Actúa como la "Capa de Puerto"
 permitiendo que la API sea independiente de los registros del microcontrolador.
 */

#ifndef API_GPIO_PORT_H_
#define API_GPIO_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/* --- PROTOCOLOS DE TECLADO MATRICIAL (Capa de Port) --- */

/**
  Coloca todas las filas del teclado en estado lógico alto.
 Se utiliza para resetear el estado de las líneas antes de iniciar un nuevo escaneo.
 */
void Port_Keypad_SetAllRowsHigh(void);

/**
 Pone una fila específica en bajo (GND) para habilitar la lectura.
 param row Índice de la fila (0 a 3) a activar.
 */
void Port_Keypad_SetRowLow(uint8_t row);

/**
 Lee el estado lógico de una columna específica.
 param col Índice de la columna (0 a 3) a sensar.
 return true si la columna detecta una conexión a masa (tecla presionada),
 false si permanece en estado alto (pull-up).
 */
bool Port_Keypad_ReadColumn(uint8_t col);


/* GESTIÓN DEL INDICADOR VISUAL (LED DE ESTADO) */

/**
 Controla de forma manual el encendido o apagado del LED de estado.
 param state Estado deseado (true para ON, false para OFF).
 */
void Port_GPIO_SetStatusLED(bool state);

/**
 Conmuta el estado actual del LED (Toggle).
 Esta función es vital para la señalización visual
 no bloqueante dentro de la MEF. Se asignó al pin PA8 para evitar el conflicto
 eléctrico del pin PA5 (LED original) con la señal de reloj del bus SPI1
 compartido con la tarjeta SD.
 */
void Port_GPIO_ToggleStatusLED(void);

#endif /* API_GPIO_PORT_H_ */
