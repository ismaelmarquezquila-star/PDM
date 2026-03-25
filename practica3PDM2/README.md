#Práctica 3: Modularización y Retardos No Bloqueantes

Este proyecto implementa un módulo de software (API) para gestionar retardos no bloqueantes en sistemas embebidos, utilizando como base la arquitectura de la placa NUCLEO-F4xx.

## Objetivo
El propósito es encapsular la lógica de temporización en un módulo independiente (API_delay), permitiendo que el microcontrolador realice otras tareas mientras espera que transcurra un tiempo determinado.

## Estructura del Proyecto
Siguiendo las buenas prácticas de modularización, la estructura se organiza de la siguiente manera:
- **Drivers/API/Inc/API_delay.h**: Prototipos de funciones y definición de la estructura \`delay_t\`.
- **Drivers/API/Src/API_delay.c**: Implementación de la lógica de temporización.
- **Core/Src/main.c**: Aplicación principal que utiliza la API para generar secuencias de LED.

## Implementación Técnica
Se definió un tipo de dato estructurado para gestionar cada instancia de retardo:

\`\`\`c
typedef struct {
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
\`\`\`

### Funciones Principales
delayInit: Inicializa el retardo con una duración específica.
delayRead: Verifica si el tiempo ha expirado.
delayWrite: Permite actualizar la duración del retardo dinámicamente.

Secuencia de Ejecución
El programa hace titilar el LED de la placa siguiendo esta secuencia de 
tiempos (en ms): {500, 100, 100, 1000}
