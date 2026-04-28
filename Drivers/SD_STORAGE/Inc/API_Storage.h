#ifndef API_STORAGE_H_
#define API_STORAGE_H_

#include "SD_port.h"      // Ya trae bool_t y stdbool
#include "API_MPU6050.h"  // Necesario para BoatStatus_t

bool_t API_Storage_Init(void);
bool_t API_Storage_OpenFile(const char* filename);
bool_t API_Storage_LogData(BoatStatus_t data);
bool_t API_Storage_CloseFile(void);
#endif
