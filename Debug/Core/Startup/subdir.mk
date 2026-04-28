################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f446retx.s 

OBJS += \
./Core/Startup/startup_stm32f446retx.o 

S_DEPS += \
./Core/Startup/startup_stm32f446retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Core/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/API_Drivers/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Core/App/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/DELAY/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/KEYPAD/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/LCD_I2C/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/MPU6050/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/SD_STORAGE/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/UART_LOG/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f446retx.d ./Core/Startup/startup_stm32f446retx.o

.PHONY: clean-Core-2f-Startup

