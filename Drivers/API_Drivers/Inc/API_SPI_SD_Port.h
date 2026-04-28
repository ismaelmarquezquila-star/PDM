/**
 API_SPI_SD_Port.h
 Ismael Farid Marquez Quila
  Capa de abstracción de bajo nivel para el almacenamiento en tarjeta SD.
 Este archivo define la interfaz entre el middleware FatFs y el hardware
 SPI del STM32F446RE. Implementa las funciones requeridas por el driver diskio.
 */

#ifndef __API_SPI_SD_PORT_H
#define __API_SPI_SD_PORT_H

#include "stm32f4xx_hal.h"
#include "ff.h"
#include "diskio.h"
#include "main.h" /* Inclusión vital para acceder a las definiciones de pines de CubeMX */

/* GESTIÓN DINÁMICA DEL CHIP SELECT (CS)
 DECISIÓN DE DISEÑO: Se implementa una lógica de selección condicional para el pin CS.
 Esto permite que el driver sea robusto y portátil: si el usuario redefine el pin
 en el archivo .ioc de CubeMX, el código se adapta automáticamente.
 De lo contrario, se utiliza un valor por defecto para evitar errores de compilación.
 */
#ifdef SD_CS_Pin
	#define SD_CS_PORT SD_CS_GPIO_Port
	#define SD_CS_PIN  SD_CS_Pin
#else
	/* Valor de respaldo en caso de falta de definición en main.h */
	#define SD_CS_PORT GPIOA
	#define SD_CS_PIN  GPIO_PIN_8
#endif

/* Prototipos de funciones para el driver FatFs ------------------------------*/
/* Estas funciones son los callbacks obligatorios que el sistema de archivos
   invoca para realizar operaciones crudas sobre los sectores de la SD. */

/**
 Inicializa el medio físico (Tarjeta SD) en modo SPI.
 */
DSTATUS SD_disk_initialize (BYTE pdrv);

/**
 Devuelve el estado actual de la unidad de disco.
 */
DSTATUS SD_disk_status (BYTE pdrv);

/**
 Lee sectores de datos desde la tarjeta SD hacia un buffer de memoria.
 */
DRESULT SD_disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);

/**
  Escribe sectores de datos desde un buffer hacia la tarjeta SD.
 Indispensable para la persistencia del archivo LOG.CSV.
 */
DRESULT SD_disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);

/**
 Control de funciones misceláneas (sincronización, tamaño de sector, etc).
 */
DRESULT SD_disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);

#endif /* __API_SPI_SD_PORT_H */
