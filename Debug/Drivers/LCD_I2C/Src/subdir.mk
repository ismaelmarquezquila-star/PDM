################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD_I2C/Src/API_LCD.c \
../Drivers/LCD_I2C/Src/LCD_port.c 

OBJS += \
./Drivers/LCD_I2C/Src/API_LCD.o \
./Drivers/LCD_I2C/Src/LCD_port.o 

C_DEPS += \
./Drivers/LCD_I2C/Src/API_LCD.d \
./Drivers/LCD_I2C/Src/LCD_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD_I2C/Src/%.o Drivers/LCD_I2C/Src/%.su Drivers/LCD_I2C/Src/%.cyclo: ../Drivers/LCD_I2C/Src/%.c Drivers/LCD_I2C/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/API_Drivers/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Core/App/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/DELAY/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/KEYPAD/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/LCD_I2C/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/MPU6050/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/SD_STORAGE/Inc" -I"C:/Users/Asus/STM32CubeIDE/workspace_2.1.1/TRABAJO_PRACTICO_PdMFINAL/Drivers/UART_LOG/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LCD_I2C-2f-Src

clean-Drivers-2f-LCD_I2C-2f-Src:
	-$(RM) ./Drivers/LCD_I2C/Src/API_LCD.cyclo ./Drivers/LCD_I2C/Src/API_LCD.d ./Drivers/LCD_I2C/Src/API_LCD.o ./Drivers/LCD_I2C/Src/API_LCD.su ./Drivers/LCD_I2C/Src/LCD_port.cyclo ./Drivers/LCD_I2C/Src/LCD_port.d ./Drivers/LCD_I2C/Src/LCD_port.o ./Drivers/LCD_I2C/Src/LCD_port.su

.PHONY: clean-Drivers-2f-LCD_I2C-2f-Src

