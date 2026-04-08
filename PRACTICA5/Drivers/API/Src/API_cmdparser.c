#include "API_cmdparser.h"
#include "API_uart.h"
#include "main.h"  /* IMPORTANTE: Para que reconozca UART_HandleTypeDef y HAL_OK */
#include <string.h>
#include <ctype.h>

/* Estados internos de la MEF */
typedef enum {
    CMD_IDLE,
    CMD_RECEIVING,
    CMD_PROCESS,
    CMD_EXEC,
    CMD_ERROR
} cmd_state_t;

static cmd_state_t currentState = CMD_IDLE;
static uint8_t cmdBuffer[CMD_MAX_LINE];
static uint16_t cmdIndex = 0;

/* Prototipo de función privada */
static void cmdProcessLine(void);

void cmdParserInit(void) {
    currentState = CMD_IDLE;
    cmdIndex = 0;
    memset(cmdBuffer, 0, CMD_MAX_LINE);
}

void cmdPoll(void) {
    uint8_t charIn;
    extern UART_HandleTypeDef huart2;

    /* Intenta recibir 1 byte sin bloquear */
    if (HAL_UART_Receive(&huart2, &charIn, 1, 0) == HAL_OK) {

        switch (currentState) {
            case CMD_IDLE:
                if (charIn != '\r' && charIn != '\n' && charIn != ' ') {
                    cmdIndex = 0;
                    cmdBuffer[cmdIndex++] = charIn;
                    currentState = CMD_RECEIVING;
                }
                break;

            case CMD_RECEIVING:
                if (charIn == '\r' || charIn == '\n') {
                    cmdBuffer[cmdIndex] = '\0';
                    currentState = CMD_PROCESS;
                } else {
                    if (cmdIndex < (CMD_MAX_LINE - 1)) {
                        cmdBuffer[cmdIndex++] = charIn;
                        /* Echo básico */
                        uartSendStringSize(&charIn, 1);
                    } else {
                        currentState = CMD_ERROR;
                    }
                }
                break;

            default:
                break;
        }
    }

    if (currentState == CMD_PROCESS) {
        cmdProcessLine();
        currentState = CMD_EXEC;
    }
    else if (currentState == CMD_EXEC) {
        currentState = CMD_IDLE;
    }
    else if (currentState == CMD_ERROR) {
        uartSendString((uint8_t*)"\r\nERROR: line too long\r\n");
        currentState = CMD_IDLE;
    }
}

static void cmdProcessLine(void) {
    /* 1. Eliminamos posibles caracteres de control al final (\r o \n) */
    char* p = (char*)cmdBuffer;
    while (*p) {
        if (*p == '\r' || *p == '\n') {
            *p = '\0';
            break;
        }
        p++;
    }

    /* 2. Ahora comparamos sin miedo */
    if (strcmp((char*)cmdBuffer, "HELP") == 0) {
        uartSendString((uint8_t*)"\r\nComandos: LED ON, LED OFF, STATUS, HELP\r\n");
    }
    else if (strcmp((char*)cmdBuffer, "LED ON") == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        uartSendString((uint8_t*)"\r\nOK: LED encendido\r\n");
    }
    else if (strcmp((char*)cmdBuffer, "LED OFF") == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        uartSendString((uint8_t*)"\r\nOK: LED apagado\r\n");
    }
    else if (strcmp((char*)cmdBuffer, "STATUS") == 0) {
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {
            uartSendString((uint8_t*)"\r\nEl LED esta ON\r\n");
        } else {
            uartSendString((uint8_t*)"\r\nEl LED esta OFF\r\n");
        }
    }
    else {
        /* Imprimimos qué es lo que la placa cree que recibió para debug */
        uartSendString((uint8_t*)"\r\nComando desconocido: [");
        uartSendString(cmdBuffer);
        uartSendString((uint8_t*)"]\r\n");
    }
}
