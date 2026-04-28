/**
  Keypad_port.c
 Ismael Farid Marquez Quila
 Capa de puerto (Port) para el teclado matricial.
Este archivo implementa la interfaz física del teclado, aislando
 los llamados al HAL de la lógica de escaneo.
 */

#include "Keypad_port.h"
#include "main.h"

void Keypad_Port_Init(void) {
    /* La configuración eléctrica de los pines se realiza en MX_GPIO_Init
       para mantener la centralización del hardware en main.c */
}

/**
 Escribe en las filas del teclado.
  Se utiliza un switch-case para garantizar un flujo de
 control determinista (Regla 1 de la NASA) y evitar el acceso indirecto a
 registros mediante punteros, aumentando la seguridad del driver.
 */
void Keypad_Port_WriteRow(uint8_t row, bool_t state) {
    GPIO_PinState pinState = (state) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    switch(row) {
        case 0: HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, pinState); break;
        case 1: HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, pinState); break;
        case 2: HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, pinState); break;
        case 3: HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, pinState); break;
    }
}

/**
Lee el estado de las columnas.
 Se asume lógica negativa (Pull-up activa). El retorno indica
 si la columna fue llevada a masa por la pulsación de una tecla.
 */
bool_t Keypad_Port_ReadCol(uint8_t col) {
    GPIO_PinState state = GPIO_PIN_SET;

    switch(col) {
        case 0: state = HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin); break;
        case 1: state = HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin); break;
        case 2: state = HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin); break;
        case 3: state = HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin); break;
    }
    return (state == GPIO_PIN_RESET);
}

void Keypad_Port_Delay(uint32_t ms) {
    /* Encapsulamiento de la función de tiempo para asegurar la portabilidad
       del driver a otras plataformas sin modificar la API. */
    HAL_Delay(ms);
}
