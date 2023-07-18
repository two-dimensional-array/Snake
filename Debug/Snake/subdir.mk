################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Snake/snake.cpp 

OBJS += \
./Snake/snake.o 

CPP_DEPS += \
./Snake/snake.d 


# Each subdirectory must supply rules for building sources it contributes
Snake/%.o Snake/%.su Snake/%.cyclo: ../Snake/%.cpp Snake/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DHD44780U_INCLUDE_CONFIG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/education/Snake/Configs" -I"C:/education/Snake/CustomDrivers/ButtonDriver" -I"C:/education/Snake/CustomDrivers/GPIO" -I"C:/education/Snake/CustomDrivers/HD44780U" -I"C:/education/Snake/Snake" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Snake

clean-Snake:
	-$(RM) ./Snake/snake.cyclo ./Snake/snake.d ./Snake/snake.o ./Snake/snake.su

.PHONY: clean-Snake

