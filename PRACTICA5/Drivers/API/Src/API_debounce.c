#include "API_debounce.h"
#include "API_delay.h"
#include "main.h"

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING
} debounceState_t;

static debounceState_t currentState;
static bool_t keyPressed;
static delay_t debounceDelay;

void debounceFSM_init(void) {
    currentState = BUTTON_UP;
    keyPressed = false;
    delayInit(&debounceDelay, 40); /* 40ms de antirrebote */
}

void debounceFSM_update(void) {
    switch (currentState) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                currentState = BUTTON_FALLING;
                delayRead(&debounceDelay); /* Inicia el delay */
            }
            break;

        case BUTTON_FALLING:
            if (delayRead(&debounceDelay)) {
                if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
                    currentState = BUTTON_DOWN;
                    keyPressed = true;
                } else {
                    currentState = BUTTON_UP;
                }
            }
            break;

        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
                currentState = BUTTON_RISING;
                delayRead(&debounceDelay);
            }
            break;

        case BUTTON_RISING:
            if (delayRead(&debounceDelay)) {
                if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
                    currentState = BUTTON_UP;
                } else {
                    currentState = BUTTON_DOWN;
                }
            }
            break;

        default:
            debounceFSM_init();
            break;
    }
}

bool_t readKey(void) {
    bool_t status = keyPressed;
    keyPressed = false;
    return status;
}
