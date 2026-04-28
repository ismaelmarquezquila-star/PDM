/**

 Implementación de la lógica de escaneo para el teclado matricial.

 */

#include "API_Keypad.h"
#include "Keypad_port.h"
#include <stddef.h>

/* CONFIGURACIÓN DEL MAPEO FÍSICO
 Se ajustó el orden de la matriz para que coincida con la
 disposición eléctrica del shield utilizado en las prácticas de la CESE.
 Intercambiar las posiciones en software evita tener que recablear el hardware
 para que la tecla física '2' devuelva el carácter '2'.
 */
static const char keys[4][4] = {
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'},
    {'A', 'B', 'C', 'D'}
};

/* VARIABLE GLOBAL PRIVADA: Se utiliza el calificador static para encapsular
 el estado de la última tecla presionada, permitiendo implementar una
 lógica de detección por flanco sin exponer la variable al exterior. */
static char last_key = '\0';

void API_Keypad_Init(void) {
    /* Inicialización de los GPIO mediante la capa de puerto */
    Keypad_Port_Init();

    /* Aseguramos un estado conocido: todas las filas en ALTO (lógica negativa) */
    for(uint8_t i=0; i<4; i++) {
        Keypad_Port_WriteRow(i, true);
    }
}

/**
 Algoritmo de escaneo matricial.

 */
char API_Keypad_GetChar(void) {
    char current_key = '\0';

    /* REGLA DE LA NASA (Power of Ten): Bucles con límite fijo para garantizar
       que el tiempo de respuesta sea constante y predecible. */
    for (uint8_t r = 0; r < 4; r++) {
        /* Activamos la fila (Lógica Negativa) */
        Keypad_Port_WriteRow(r, false);

        for (uint8_t c = 0; c < 4; c++) {
            if (Keypad_Port_ReadCol(c)) {
                current_key = keys[r][c];
            }
        }

        /* Desactivamos la fila antes de pasar a la siguiente */
        Keypad_Port_WriteRow(r, true);

        /* Optimizamos: si ya encontramos una tecla, salimos del escaneo */
        if (current_key != '\0') break;
    }

    /* LÓGICA DE DETECCIÓN POR FLANCO
     Para evitar el ingreso de múltiples caracteres
     ante una sola pulsación prolongada (típico error en menús), solo se
     retorna el carácter cuando detectamos un cambio de estado.
     Esto actúa como un antirrebote (debounce) simplificado por software.
     */
    if (current_key != last_key) {
        last_key = current_key;
        return current_key;
    }

    /* Si se soltó la tecla, reseteamos el estado para permitir una nueva pulsación */
    if (current_key == '\0') {
        last_key = '\0';
    }

    return '\0';
}
