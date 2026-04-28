#include "App_DataLogger_MEF.h"
#include "API_LCD.h"
#include "API_Keypad.h"
#include "API_MPU6050.h"
#include "API_Storage.h"
#include "API_UART.h"
#include "API_Delay.h"
#include <stdio.h>

typedef enum {
    STATE_INIT,
    STATE_IDLE,
    STATE_LOGGING,
    STATE_ERROR
} SystemState_t;

static SystemState_t currentState;

static void LCD_PrintCleanLine(uint8_t row, char* msg) {
    char buffer[17];
    snprintf(buffer, sizeof(buffer), "%-16s", msg);
    API_LCD_PutCur(row, 0);
    API_LCD_SendString(buffer);
}

void App_DataLogger_Init(void) {
    currentState = STATE_INIT;
    API_Delay_Init();
    API_UART_Init();
    API_LCD_Init();
    API_Keypad_Init();
    API_UART_SendString("\r\n--- SISTEMA DE MONITOREO CANOA OK ---\r\n");
}


void App_DataLogger_Update(void) {
    char key;
    char lcdBuffer[17];
    BoatStatus_t status;
    static uint32_t lastTick = 0;

    // --- LÓGICA DE TIEMPO NO BLOQUEANTE PARA EL LED ---
    static delay_t ledDelay;
    static bool_t ledConfigured = false;

    if (!ledConfigured) {
        // AJUSTE: 62ms para que prenda y apague rápido.
        // 62ms prendido + 62ms apagado = 124ms (aprox 1/8 de segundo).
        API_Delay_Config(&ledDelay, 62);
        ledConfigured = true;
    }

    // --- CONTROL DEL LED SEGURO EN EL PIN PA8 (D7) ---
    // Usamos GPIO_PIN_8 porque PA5 interfiere con la SD
    if (currentState == STATE_LOGGING) {
        if (API_Delay_IsDone(&ledDelay)) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        }
    } else {
        // Apagado total en IDLE, INIT o ERROR
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    }

    switch (currentState) {
        case STATE_INIT:
            API_UART_SendString("Iniciando MPU6050 y SD...\r\n");
            API_MPU6050_Init();
            HAL_Delay(100);

            if (API_Storage_Init()) {
                API_UART_SendString("SD Lista.\r\n");
                LCD_PrintCleanLine(0, "SD OK! 1:START");
                currentState = STATE_IDLE;
            } else {
                API_UART_SendString("Error SD.\r\n");
                currentState = STATE_ERROR;
            }
            break;

        case STATE_IDLE:
            key = API_Keypad_GetChar();
            status = API_MPU6050_GetStability();

            if (HAL_GetTick() - lastTick > 300) {
                lastTick = HAL_GetTick();
                if (status.pitch == 0.0f && status.roll == 0.0f) API_MPU6050_Init();

                snprintf(lcdBuffer, sizeof(lcdBuffer), "P:%.1f R:%.1f", status.pitch, status.roll);
                LCD_PrintCleanLine(1, lcdBuffer);
                API_UART_LogStability(status.pitch, status.roll);
            }

            if (key == '1') {
                if (API_Storage_OpenFile("LOG.CSV")) {
                    LCD_PrintCleanLine(0, "GRABANDO...");
                    currentState = STATE_LOGGING;
                }
            }
            break;

        case STATE_LOGGING:
            key = API_Keypad_GetChar();

            if (key == '2') {
                API_Storage_CloseFile();
                LCD_PrintCleanLine(0, "DETENIDO OK");
                HAL_Delay(1000);
                currentState = STATE_INIT;
                return;
            }

            status = API_MPU6050_GetStability();
            if (HAL_GetTick() - lastTick > 200) {
                lastTick = HAL_GetTick();
                snprintf(lcdBuffer, sizeof(lcdBuffer), "P:%.1f R:%.1f", status.pitch, status.roll);
                LCD_PrintCleanLine(1, lcdBuffer);

                API_Storage_LogData(status);
                API_UART_LogStability(status.pitch, status.roll);
            }
            break;

        case STATE_ERROR:
            LCD_PrintCleanLine(0, "ERR: REINT CON #");
            key = API_Keypad_GetChar();
            if (key == '#') currentState = STATE_INIT;
            break;
    }
}
