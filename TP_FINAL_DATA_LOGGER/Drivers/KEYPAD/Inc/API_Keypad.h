/**
 * @file API_Keypad.h
 * @author Ismael Farid Marquez Quila
 * @brief Interfaz lógica para el manejo del teclado matricial.
 * @details Este módulo proporciona una capa de abstracción para la detección
 * de entradas de usuario, permitiendo que la aplicación principal (Canoa)
 * reciba caracteres sin conocer los detalles del barrido eléctrico.
 */

#ifndef API_KEYPAD_H_
#define API_KEYPAD_H_

#include <stdint.h>

/* Este encabezado define funciones agnósticas al hardware. La implementación
  de los tiempos de antirrebote (debounce) y el mapeo físico de los pines
 se delegan a la capa 'Port' para cumplir con el desacoplamiento de capas.
 */

/**
 Inicializa el módulo del teclado.
 Llama internamente a la configuración de los pines GPIO y prepara
 el estado inicial de las filas para el escaneo.
 */
void API_Keypad_Init(void);

/**
 Obtiene el último carácter presionado de forma no bloqueante.

 */
char API_Keypad_GetChar(void);

#endif /* API_KEYPAD_H_ */
