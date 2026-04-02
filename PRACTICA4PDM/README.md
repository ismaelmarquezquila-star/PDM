# Práctica 4 - Programación de Microcontroladores (PDM)

Este proyecto implementa un sistema de control de periféricos utilizando una **Máquina de Estados Finitos (FSM)** para el manejo de un pulsador con antirrebote (debounce) y el control de retardos no bloqueantes en una placa **STM32 Nucleo-F446RE**.

## 📋 Descripción
El objetivo de la práctica es alternar entre diferentes frecuencias de parpadeo de un LED (LD2) cada vez que se presiona el pulsador azul (B1). 

### Características principales:
* **Antirrebote (Debounce) por Software:** Implementado mediante una FSM con estados: `BUTTON_UP`, `BUTTON_FALLING`, `BUTTON_DOWN` y `BUTTON_RAISING`.
* **Retardos No Bloqueantes:** Uso de la API `delay_t` basada en `HAL_GetTick()` para permitir que el procesador realice múltiples tareas simultáneamente.
* **Modularización:** El código está organizado en drivers específicos (`API_debounce` y `API_delay`).

## 🛠️ Hardware Utilizado
* **Placa:** STM32F446RE (Cortex-M4).
* **LED de usuario:** LD2 (Pin PA5).
* **Botón de usuario:** B1 (Pin PC13 - Lógica Negativa).

## 🚀 Estructura del Código
* `Core/Src/main.c`: Lógica principal y configuración del sistema.
* `Drivers/API/Src/API_debounce.c`: Lógica de la máquina de estados del botón.
* `Drivers/API/Src/API_delay.c`: Implementación de retardos no bloqueantes.
* `Drivers/API/Inc/`: Archivos de cabecera (.h) correspondientes.

## ⚙️ Funcionamiento
1. Al iniciar, el LED parpadea a una frecuencia de **500ms**.
2. Al presionar el botón azul (B1), la FSM detecta el flanco descendente y valida la presión tras **40ms**.
3. Se cambia el índice del arreglo de tiempos `TIEMPOS[] = {500, 100}`, modificando la velocidad del LED.
4. El sistema es totalmente asíncrono; no se utiliza la función `HAL_Delay()`.


