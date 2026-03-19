Nombre completo del alumno: Ismael Farid Marquez Quila

Asignatura: Programación de microprocesadores

Trabajo práctico: Practica 0
Nombre completo del alumno: Ismael Farid Marquez Quila
Asignatura: Programación de microprocesadores
Trabajo práctico: Práctica 2

#Configuración de Hardware (Proyecto Original)

Este proyecto fue desarrollado, configurado y probado utilizando la siguiente arquitectura de hardware:

* Placa de Desarrollo: NUCLEO-F446RE
* Microcontrolador: STM32F446RETx
* Core:** ARM Cortex-M4
* Oscilador / Reloj: HSI (Configuración por defecto del IDE)

Periféricos y Mapeo de Pines Utilizados

Para la evaluación y revisión de la lógica de este proyecto, tener en cuenta la siguiente asignación de pines físicos de la placa F446RE:

| Componente | Etiqueta HAL | Puerto / Pin físico |
| :--- | :--- | :--- |
| **LED Verde (User LED)** | `LD2_GPIO_Port` / `LD2_Pin` | **PA5** |
| **Botón Azul (User Button)** | `B1_GPIO_Port` / `B1_Pin` | **PC13** |

Resumen de la Práctica

Implementación de una biblioteca de temporización no bloqueante (`delay_t`) basada en la lectura del `SysTick` (`HAL_GetTick()`).
Se incluye la lógica para la secuencia dinámica de parpadeo del LED principal utilizando arreglos de tiempos y un contador de semiperiodos.
