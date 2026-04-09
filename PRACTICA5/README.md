Práctica 5: Implementación de Máquina de Estados Finos (FSM)
 El objetivo principal es el diseño e implementación de una Máquina de Estados Finos (FSM) para el control de un sistema de secuencias de LEDs, utilizando una arquitectura modular y buenas prácticas de programación en C para sistemas embebidos.

Descripción
La práctica se centra en la transición entre diferentes estados lógicos basados en entradas externas (pulsadores) y temporizaciones no bloqueantes. 
Características principales:
Gestión de Estados: Implementación mediante switch-case y enumeraciones (enum).

Temporización No Bloqueante: Uso de la función HAL_GetTick() para el manejo de retardos.

Manejo de Antirrebote (Debounce): Software dedicado para filtrar el ruido mecánico del pulsador.

Modularización: Código organizado en archivos de cabecera (.h) y archivos fuente (.c).
