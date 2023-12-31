################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CustomDrivers/ButtonDriver/button_driver.c 

C_DEPS += \
./CustomDrivers/ButtonDriver/button_driver.d 

OBJS += \
./CustomDrivers/ButtonDriver/button_driver.o 


# Each subdirectory must supply rules for building sources it contributes
CustomDrivers/ButtonDriver/%.o CustomDrivers/ButtonDriver/%.su CustomDrivers/ButtonDriver/%.cyclo: ../CustomDrivers/ButtonDriver/%.c CustomDrivers/ButtonDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DHD44780U_INCLUDE_CONFIG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Configs -I../Snake -I../CustomDrivers/ButtonDriver -I../CustomDrivers/GPIO -I../CustomDrivers/HD44780U -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CustomDrivers-2f-ButtonDriver

clean-CustomDrivers-2f-ButtonDriver:
	-$(RM) ./CustomDrivers/ButtonDriver/button_driver.cyclo ./CustomDrivers/ButtonDriver/button_driver.d ./CustomDrivers/ButtonDriver/button_driver.o ./CustomDrivers/ButtonDriver/button_driver.su

.PHONY: clean-CustomDrivers-2f-ButtonDriver

