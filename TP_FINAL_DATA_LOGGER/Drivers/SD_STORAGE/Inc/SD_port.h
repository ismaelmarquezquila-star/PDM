#ifndef SD_PORT_H_
#define SD_PORT_H_

#include "ff_gen_drv.h"
#include <stdbool.h>    // Necesario para bool
#include <stdint.h>     // Necesario para uint8_t, etc.

typedef bool bool_t;    // Definimos bool_t para que API_Storage lo reconozca

/* Prototipos de bajo nivel que ya escribiste en SD_port.c */
void SD_Port_Init(void);
void SD_Port_CS_Low(void);
void SD_Port_CS_High(void);
void SD_Port_WriteByte(uint8_t data);
uint8_t SD_Port_ReadByte(void);
void SD_Port_Delay(uint32_t ms);

/* Prototipos para FatFs (user_diskio.c) */
DSTATUS SD_disk_initialize(BYTE pdrv);
DSTATUS SD_disk_status(BYTE pdrv);
DRESULT SD_disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT SD_disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT SD_disk_ioctl(BYTE pdrv, BYTE cmd, void* buff);

#endif
