

#include "API_GPIO_Port.h"
#include "main.h"

/* --- ESTRUCTURAS DE DATOS PRIVADAS (Encapsulamiento)
 */

/* Mapeo de FILAS siguiendo la configuración del shield de la CESE */
static GPIO_TypeDef* row_ports[] = {R1_GPIO_Port, R2_GPIO_Port, R3_GPIO_Port, R4_GPIO_Port};
static uint16_t row_pins[] = {R1_Pin, R2_Pin, R3_Pin, R4_Pin};

/* Mapeo de COLUMNAS */
static GPIO_TypeDef* col_ports[] = {C1_GPIO_Port, C2_GPIO_Port, C3_GPIO_Port, C4_GPIO_Port};
static uint16_t col_pins[] = {C1_Pin, C2_Pin, C3_Pin, C4_Pin};

/**
Resetea todas las filas al estado inactivo (ALTO).

 */
void Port_Keypad_SetAllRowsHigh(void) {
    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(row_ports[i], row_pins[i], GPIO_PIN_SET);
    }
}

/**
  Activa una fila específica poniendo su estado en BAJO.
El teclado opera con lógica negativa; al poner la fila en GND,
 cerramos el circuito permitiendo que la columna detecte la pulsación.
 */
void Port_Keypad_SetRowLow(uint8_t row) {
    if (row < 4) {
        HAL_GPIO_WritePin(row_ports[row], row_pins[row], GPIO_PIN_RESET);
    }
}

/**
Lee el estado de una columna específica.
.
 */
bool Port_Keypad_ReadColumn(uint8_t col) {
    if (col < 4) {
        /* Si el pin lee 0 (RESET), significa que la tecla cerró el contacto a masa */
        return (HAL_GPIO_ReadPin(col_ports[col], col_pins[col]) == GPIO_PIN_RESET);
    }
    return false;
}

/*  GESTIÓN DEL INDICADOR VISUAL (Feedback de usuario) */

/**
 Control manual del estado del LED.
  Se utiliza el pin PA8 en lugar del PA5 original de la
 placa Nucleo. Esto se debe a que el pin PA5 comparte línea con el reloj (SCK)
 del bus SPI1. Al grabar en la SD, el parpadeo del LED original generaba
 ruido en la señal de reloj, comprometiendo la integridad de los datos.
 */
void Port_GPIO_SetStatusLED(bool state) {
    /* Mantenemos el pin PA8 para el LED externo de estado */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**

 Esta función es llamada por la MEF de forma no bloqueante para
 indicar que el sistema está en proceso de escritura en la memoria SD.
 */
void Port_GPIO_ToggleStatusLED(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
}
