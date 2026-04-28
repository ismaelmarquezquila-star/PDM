################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API_Drivers/Src/API_Delay_Port.c \
../Drivers/API_Drivers/Src/API_GPIO_Port.c 

OBJS += \
./Drivers/API_Drivers/Src/API_Delay_Port.o \
./Drivers/API_Drivers/Src/API_GPIO_Port.o 

C_DEPS += \
./Drivers/API_Drivers/Src/API_Delay_Port.d \
./Drivers/API_Drivers/Src/API_GPIO_Port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API_Drivers/Src/%.o Drivers/API_Drivers/Src/%.su Drivers/API_Drivers/Src/%.cyclo: ../Drivers/API_Drivers/Src/%.c Drivers/API_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/API_Drivers/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Core/App/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/DELAY/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/KEYPAD/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/LCD_I2C/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/MPU6050/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/SD_STORAGE/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/UART_LOG/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API_Drivers-2f-Src

clean-Drivers-2f-API_Drivers-2f-Src:
	-$(RM) ./Drivers/API_Drivers/Src/API_Delay_Port.cyclo ./Drivers/API_Drivers/Src/API_Delay_Port.d ./Drivers/API_Drivers/Src/API_Delay_Port.o ./Drivers/API_Drivers/Src/API_Delay_Port.su ./Drivers/API_Drivers/Src/API_GPIO_Port.cyclo ./Drivers/API_Drivers/Src/API_GPIO_Port.d ./Drivers/API_Drivers/Src/API_GPIO_Port.o ./Drivers/API_Drivers/Src/API_GPIO_Port.su

.PHONY: clean-Drivers-2f-API_Drivers-2f-Src

