################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../API/Src/API_Delay.c \
../API/Src/API_Keypad.c \
../API/Src/API_LCD.c \
../API/Src/API_MPU6050.c \
../API/Src/API_Storage.c \
../API/Src/API_UART.c 

OBJS += \
./API/Src/API_Delay.o \
./API/Src/API_Keypad.o \
./API/Src/API_LCD.o \
./API/Src/API_MPU6050.o \
./API/Src/API_Storage.o \
./API/Src/API_UART.o 

C_DEPS += \
./API/Src/API_Delay.d \
./API/Src/API_Keypad.d \
./API/Src/API_LCD.d \
./API/Src/API_MPU6050.d \
./API/Src/API_Storage.d \
./API/Src/API_UART.d 


# Each subdirectory must supply rules for building sources it contributes
API/Src/%.o API/Src/%.su API/Src/%.cyclo: ../API/Src/%.c API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/usuario/Desktop/Proyecto/lse/GITCESE/PdM_workspace/TRABAJO_PRACTICO_PdM2/Drivers/API_Drivers/Inc" -I"C:/Users/usuario/Desktop/Proyecto/lse/GITCESE/PdM_workspace/TRABAJO_PRACTICO_PdM2/API/Inc" -I"C:/Users/usuario/Desktop/Proyecto/lse/GITCESE/PdM_workspace/TRABAJO_PRACTICO_PdM2/Core/App/Inc" -I"C:/Users/usuario/Desktop/Proyecto/lse/GITCESE/PdM_workspace/TRABAJO_PRACTICO_PdM2/API" -I"C:/Users/usuario/Desktop/Proyecto/lse/GITCESE/PdM_workspace/TRABAJO_PRACTICO_PdM2/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-API-2f-Src

clean-API-2f-Src:
	-$(RM) ./API/Src/API_Delay.cyclo ./API/Src/API_Delay.d ./API/Src/API_Delay.o ./API/Src/API_Delay.su ./API/Src/API_Keypad.cyclo ./API/Src/API_Keypad.d ./API/Src/API_Keypad.o ./API/Src/API_Keypad.su ./API/Src/API_LCD.cyclo ./API/Src/API_LCD.d ./API/Src/API_LCD.o ./API/Src/API_LCD.su ./API/Src/API_MPU6050.cyclo ./API/Src/API_MPU6050.d ./API/Src/API_MPU6050.o ./API/Src/API_MPU6050.su ./API/Src/API_Storage.cyclo ./API/Src/API_Storage.d ./API/Src/API_Storage.o ./API/Src/API_Storage.su ./API/Src/API_UART.cyclo ./API/Src/API_UART.d ./API/Src/API_UART.o ./API/Src/API_UART.su

.PHONY: clean-API-2f-Src

