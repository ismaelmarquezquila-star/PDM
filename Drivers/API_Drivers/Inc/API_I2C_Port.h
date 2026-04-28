/**
 * @file API_I2C_PORT.h
 * @author Ismael Farid Marquez Quila
 * @brief Capa de abstracción para el protocolo de comunicación I2C.
 * @details Este puerto actúa como el puente entre los drivers genéricos
 * y el hardware específico del STM32, encapsulando las funciones del HAL.
 */

#ifndef API_I2C_PORT_H_
#define API_I2C_PORT_H_

#include <stdbool.h>
#include <stdint.h>

/**
 Transmisión genérica de datos por el bus I2C.
 Utilizada principalmente por el driver del LCD para el envío de nibbles.
 */
bool Port_I2C_Transmit(uint16_t devAddr, uint8_t *pData, uint16_t size);

/**
 Lectura de registros específicos de un periférico I2C.
 param regAddr Dirección del registro interno (ej. WHO_AM_I en MPU6050).
 */
bool Port_I2C_ReadRegister(uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t size);

/**
 Escritura de registros de control en un periférico I2C.
 Se implementan funciones orientadas a registros
 para facilitar la configuración de la IMU, permitiendo que la API_MPU6050
 sea agnóstica al hardware y se enfoque solo en la lógica del sensor.
 */
bool Port_I2C_WriteRegister(uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t size);

#endif /* API_I2C_PORT_H_ */
