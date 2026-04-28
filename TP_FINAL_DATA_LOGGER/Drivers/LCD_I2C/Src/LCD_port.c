/**
  LCD_port.c
 Ismael Farid Marquez Quila
 Implementación de bajo nivel (Port) para el display LCD.

 */

#include "LCD_port.h"
#include "i2c.h" /* Provee el handle hi2c1 generado por el microcontrolador */

/**
 Transmisión de bytes por el bus I2C específico de la placa.
Se encapsula el llamado a 'HAL_I2C_Master_Transmit' para que
 la lógica de la pantalla no dependa de los nombres de los manejadores de ST.
 param size Cantidad de bytes a enviar (nibbles empaquetados).
 return bool_t True si el bus respondió correctamente, False en caso de error.
 */
bool_t LCD_Port_I2C_Transmit(uint16_t devAddr, uint8_t *pData, uint16_t size) {

    /* Se utiliza un timeout de 100ms para asegurar que el sistema no se bloquee
       indefinidamente si el expansor I2C de la pantalla se desconecta. */
    if (HAL_I2C_Master_Transmit(&hi2c1, devAddr, pData, size, 100) == HAL_OK) {
        return true;
    }
    return false;
}

/**
  Wrapper para retardos de hardware necesarios en la inicialización del LCD.
 */
void LCD_Port_Delay(uint32_t ms) {
    /* Se utiliza el servicio de tiempo nativo del STM32F446RE */
    HAL_Delay(ms);
}
