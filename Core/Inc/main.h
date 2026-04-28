/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  * : PROYECTO DATALOGGER NAVAL - CESE UBA
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define C2_Pin GPIO_PIN_0
#define C2_GPIO_Port GPIOA
#define C1_Pin GPIO_PIN_1
#define C1_GPIO_Port GPIOA
//#define SD_CS_Pin GPIO_PIN_4
//#define SD_CS_GPIO_Port GPIOA
#define R3_Pin GPIO_PIN_0
#define R3_GPIO_Port GPIOB
#define C3_Pin GPIO_PIN_7
#define C3_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOA
#define C4_Pin GPIO_PIN_9
#define C4_GPIO_Port GPIOA
#define R1_Pin GPIO_PIN_10
#define R1_GPIO_Port GPIOA
#define R2_Pin GPIO_PIN_3
#define R2_GPIO_Port GPIOB
#define R4_Pin GPIO_PIN_5
#define R4_GPIO_Port GPIOB
#define SD_CSB6_Pin GPIO_PIN_6
#define SD_CSB6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* --- CONFIGURACIÓN DE LA SD (CABLE MOVIDO A D10) --- */
/* D10 en la placa Nucleo-F446RE corresponde internamente a PB6 */
#define SD_CS_Pin           GPIO_PIN_6
#define SD_CS_GPIO_Port     GPIOB

/* --- PINES DEL TECLADO MATRICIAL 4x4 --- */
/* Columnas (Entradas con Pull-up) */
#define C1_Pin              GPIO_PIN_1
#define C1_GPIO_Port        GPIOA
#define C2_Pin              GPIO_PIN_0
#define C2_GPIO_Port        GPIOA
#define C3_Pin              GPIO_PIN_7
#define C3_GPIO_Port        GPIOC
#define C4_Pin              GPIO_PIN_9
#define C4_GPIO_Port        GPIOA

/* Filas (Salidas) */
#define R1_Pin              GPIO_PIN_10
#define R1_GPIO_Port        GPIOA
#define R2_Pin              GPIO_PIN_3
#define R2_GPIO_Port        GPIOB
#define R3_Pin              GPIO_PIN_0
#define R3_GPIO_Port        GPIOB
#define R4_Pin              GPIO_PIN_5
#define R4_GPIO_Port        GPIOB

/* --- CONFIGURACIÓN DE PERIFÉRICOS I2C (MPU6050 y LCD) --- */
/* SDA -> PB9, SCL -> PB8 */

/* --- MANEJADORES DE PERIFÉRICOS --- */
#define I2C_PORT_HANDLE     hi2c1
#define DEBUG_UART_HANDLE   huart2

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
