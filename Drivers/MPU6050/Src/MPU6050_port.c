/**

 Ismael Farid Marquez Quila
 Implementación de bajo nivel (Port) para el sensor inercial.
 *
 */

#include "MPU6050_port.h"
#include "i2c.h"

/**
 Lectura de registros internos del sensor.
  Se utiliza 'HAL_I2C_Mem_Read' en lugar de una recepción
 maestra estándar porque el MPU6050 requiere el envío previo de la dirección
 del registro interno (protocolo Register-to-Data).
 */
bool_t MPU_Port_ReadRegister(uint16_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t size) {
    /* Se define un timeout de 100ms para evitar bloqueos del sistema en caso
       de fallos físicos en el bus I2C de la canoa. */
    if (HAL_I2C_Mem_Read(&hi2c1, devAddr, (uint16_t)regAddr, I2C_MEMADD_SIZE_8BIT, pData, size, 100) == HAL_OK) {
        return true;
    }
    return false;
}

/**
 Escritura de registros de configuración del sensor.
 Se utiliza el tamaño de dirección de 8 bits (I2C_MEMADD_SIZE_8BIT)
 acorde al mapa de registros del datasheet del MPU6050.
 */
bool_t MPU_Port_WriteRegister(uint16_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t size) {
    if (HAL_I2C_Mem_Write(&hi2c1, devAddr, (uint16_t)regAddr, I2C_MEMADD_SIZE_8BIT, pData, size, 100) == HAL_OK) {
        return true;
    }
    return false;
}


void MPU_Port_Delay(uint32_t ms) {
    HAL_Delay(ms);
}
