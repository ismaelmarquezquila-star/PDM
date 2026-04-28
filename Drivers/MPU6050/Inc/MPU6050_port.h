/*

Ismael Farid (Felipe)
 Carrera de Especialización en Sistemas Embebidos (CESE - UBA)
 */

#ifndef MPU6050_PORT_H_
#define MPU6050_PORT_H_

#include <stdint.h>
#include <stdbool.h>

/* * Definición de tipo de dato booleano sugerido por la cátedra
 para uniformidad en los drivers del proyecto integrador.
 */
typedef bool bool_t;

/**
 Lee una ráfaga de datos de los registros del MPU6050.
 param devAddr Dirección I2C del dispositivo.
 param regAddr Registro inicial de lectura.
 pData   Puntero al buffer donde se guardarán los datos.
 param size    Cantidad de bytes a leer.
 return bool_t True si la lectura fue exitosa (HAL_OK).
 */
bool_t MPU_Port_ReadRegister(uint16_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t size);

/**
Escribe datos en un registro específico del MPU6050.
 param devAddr Dirección I2C del dispositivo.
 param regAddr Registro donde se desea escribir.
 param pData   Puntero a los datos a enviar (ej. comando de despertar).
 param size    Cantidad de bytes a escribir.
 return bool_t True si la escritura fue exitosa.
 */
bool_t MPU_Port_WriteRegister(uint16_t devAddr, uint8_t regAddr, uint8_t *pData, uint16_t size);

/**
  Genera un retardo en milisegundos utilizando la base de tiempo del sistema.
 param ms Tiempo en milisegundos.
 */
void MPU_Port_Delay(uint32_t ms);

#endif /* MPU6050_PORT_H_ */
