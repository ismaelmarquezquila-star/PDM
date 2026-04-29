# DataLogger de Estabilidad para Embarcaciones - Proyecto Integrador CESE (UBA)

**Autor:** Ismael Farid Marquez Quila  
**Asignaturas:** Programación de Microcontroladores (PdM) y Protocolos de Comunicación en Sistemas Embebidos (PCSE).  
**Plataforma:** STM32F446RE (Nucleo-F446RE)

## 1. Descripción de la Idea
Este proyecto consiste en un **DataLogger de precisión** diseñado para monitorear la estabilidad inercial en canoas o lanchas de fibra de vidrio. El sistema mide los ángulos de inclinación (**Pitch y Roll**) en tiempo real para prevenir riesgos de navegación y permitir un análisis posterior de la dinámica de la embarcación.

## 2. Funcionalidades Principales
- **Adquisición Inercial:** Lectura de acelerometría mediante sensor MPU6050 vía I2C.
- **Cálculo de Estabilidad:** Procesamiento trigonométrico (`atan2f`) para determinar ángulos de balanceo y cabeceo.
- **Persistencia de Datos:** Almacenamiento en tarjeta microSD (formato CSV) mediante bus SPI y el middleware FatFS.
- **Interfaz de Usuario:** - Visualización de datos y estados en pantalla LCD 16x2 (vía I2C).
  - Control de inicio/parada de grabación mediante teclado matricial.
- **Telemetría:** Envío de datos procesados por UART para monitoreo remoto.

## 3. Estructura del Proyecto (Arquitectura API/Port)
Siguiendo los requerimientos de **PCSE**, el código está organizado bajo una estricta arquitectura de capas para garantizar la portabilidad:

```text
TP_FINAL_DATA_LOGGER/
├── Core/
│   ├── App/             <-- Lógica de Aplicación (MEF Principal)
│   ├── Src/Inc/         <-- Configuración HAL y main.c
├── Drivers/
│   ├── API/             <-- Capa Genérica (Lógica del Sensor y SD)
│   │   ├── Src/Inc/     <-- API_MPU6050, API_Storage, API_UART
│   └── Port/            <-- Capa de Abstracción de Hardware (Low Level)
│       ├── Src/Inc/     <-- MPU6050_port, SD_port (Acceso a HAL)
└── FATFS/               <-- Middleware para gestión de archivos en SD
| Componente | Etiqueta HAL | Puerto / Pin físico |
| :--- | :--- | :--- |
| **LED Verde (User LED)** | `LD2_GPIO_Port` / `LD2_Pin` | **PA5** |
| **Botón Azul (User Button)** | `B1_GPIO_Port` / `B1_Pin` | **PC13** |

Resumen de la Práctica

Implementación de una biblioteca de temporización no bloqueante (`delay_t`) basada en la lectura del `SysTick` (`HAL_GetTick()`).
Se incluye la lógica para la secuencia dinámica de parpadeo del LED principal utilizando arreglos de tiempos y un contador de semiperiodos.
