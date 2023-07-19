################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CustomDrivers/GPIO/gpio.cpp 

OBJS += \
./CustomDrivers/GPIO/gpio.o 

CPP_DEPS += \
./CustomDrivers/GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
CustomDrivers/GPIO/%.o CustomDrivers/GPIO/%.su CustomDrivers/GPIO/%.cyclo: ../CustomDrivers/GPIO/%.cpp CustomDrivers/GPIO/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DHD44780U_INCLUDE_CONFIG -DSTM32F407xx -c -I../Core/Inc -I../Configs -I../Snake -I../CustomDrivers/ButtonDriver -I../CustomDrivers/GPIO -I../CustomDrivers/HD44780U -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CustomDrivers-2f-GPIO

clean-CustomDrivers-2f-GPIO:
	-$(RM) ./CustomDrivers/GPIO/gpio.cyclo ./CustomDrivers/GPIO/gpio.d ./CustomDrivers/GPIO/gpio.o ./CustomDrivers/GPIO/gpio.su

.PHONY: clean-CustomDrivers-2f-GPIO

