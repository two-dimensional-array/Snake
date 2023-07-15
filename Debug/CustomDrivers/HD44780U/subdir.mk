################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CustomDrivers/HD44780U/hd44780u.c 

C_DEPS += \
./CustomDrivers/HD44780U/hd44780u.d 

OBJS += \
./CustomDrivers/HD44780U/hd44780u.o 


# Each subdirectory must supply rules for building sources it contributes
CustomDrivers/HD44780U/%.o CustomDrivers/HD44780U/%.su CustomDrivers/HD44780U/%.cyclo: ../CustomDrivers/HD44780U/%.c CustomDrivers/HD44780U/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DHD44780U_INCLUDE_CONFIG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/Configs" -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/Snake" -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/CustomDrivers/ButtonDriver" -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/CustomDrivers/GPIO" -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/CustomDrivers/HD44780U" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CustomDrivers-2f-HD44780U

clean-CustomDrivers-2f-HD44780U:
	-$(RM) ./CustomDrivers/HD44780U/hd44780u.cyclo ./CustomDrivers/HD44780U/hd44780u.d ./CustomDrivers/HD44780U/hd44780u.o ./CustomDrivers/HD44780U/hd44780u.su

.PHONY: clean-CustomDrivers-2f-HD44780U

