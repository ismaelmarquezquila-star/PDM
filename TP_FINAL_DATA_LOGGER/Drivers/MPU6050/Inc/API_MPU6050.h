#ifndef API_MPU6050_H_
#define API_MPU6050_H_

#include <stdint.h>
#include <stdbool.h>

/* Definimos la estructura */
typedef struct {
    float pitch;
    float roll;
} BoatStatus_t;

/* Ahora los prototipos */
void API_MPU6050_Init(void);
BoatStatus_t API_MPU6050_GetStability(void);

#endif /* API_MPU6050_H_ */
