/**
 API_MPU6050.c
 author Ismael Farid Marquez Quila
 Driver de aplicación para el sensor inercial.
 */

#include "API_MPU6050.h"
#include "MPU6050_port.h"
#include <math.h>

#define MPU6050_ADDR (0x68 << 1)
#define REG_PWR_MGMT_1       0x6B
#define REG_ACCEL_XOUT_H     0x3B
#define REG_WHO_AM_I         0x75
#define ACCEL_SENSITIVITY    16384.0f

void API_MPU6050_Init(void) {
    uint8_t id = 0;
    uint8_t wake_cmd = 0x00;

    /* Se valida el registro WHO_AM_I previo a la configuración
       para confirmar la integridad del bus I2C y la presencia del sensor. */
    if (MPU_Port_ReadRegister(MPU6050_ADDR, REG_WHO_AM_I, &id, 1)) {
        if (id == 0x72 || id == 0x68) {
            MPU_Port_WriteRegister(MPU6050_ADDR, REG_PWR_MGMT_1, &wake_cmd, 1);
            MPU_Port_Delay(100);
        }
    }
}

/**
 * @brief Obtiene la inclinación actual mediante trigonometría.
return BoatStatus_t Estructura con Pitch y Roll.
 */
BoatStatus_t API_MPU6050_GetStability(void) {
    BoatStatus_t status = {0.0f, 0.0f};
    uint8_t data[6];

    /* Se utiliza lectura por ráfaga (burst read) de 6 bytes para garantizar que
       los ejes X, Y y Z correspondan al mismo instante de muestreo. */
    if (MPU_Port_ReadRegister(MPU6050_ADDR, REG_ACCEL_XOUT_H, data, 6)) {
        int16_t raw_x = (int16_t)((data[0] << 8) | data[1]);
        int16_t raw_y = (int16_t)((data[2] << 8) | data[3]);
        int16_t raw_z = (int16_t)((data[4] << 8) | data[5]);

        float ax = (float)raw_x / ACCEL_SENSITIVITY;
        float ay = (float)raw_y / ACCEL_SENSITIVITY;
        float az = (float)raw_z / ACCEL_SENSITIVITY;

        /* Se emplea atan2f para el cálculo de ángulos por su robustez matemática
           ante variaciones de signo y para evitar divisiones por cero. */
        status.pitch = atan2f(ay, az) * (180.0f / 3.14159f);
        status.roll  = atan2f(-ax, sqrtf(ay * ay + az * az)) * (180.0f / 3.14159f);
    }
    return status;
}
