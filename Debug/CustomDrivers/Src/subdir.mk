################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CustomDrivers/Src/gpio.cpp \
../CustomDrivers/Src/wh1202b.cpp 

OBJS += \
./CustomDrivers/Src/gpio.o \
./CustomDrivers/Src/wh1202b.o 

CPP_DEPS += \
./CustomDrivers/Src/gpio.d \
./CustomDrivers/Src/wh1202b.d 


# Each subdirectory must supply rules for building sources it contributes
CustomDrivers/Src/%.o CustomDrivers/Src/%.su: ../CustomDrivers/Src/%.cpp CustomDrivers/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/PC/STM32CubeIDE/workspace_1.10.1/rtos/CustomDrivers/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CustomDrivers-2f-Src

clean-CustomDrivers-2f-Src:
	-$(RM) ./CustomDrivers/Src/gpio.d ./CustomDrivers/Src/gpio.o ./CustomDrivers/Src/gpio.su ./CustomDrivers/Src/wh1202b.d ./CustomDrivers/Src/wh1202b.o ./CustomDrivers/Src/wh1202b.su

.PHONY: clean-CustomDrivers-2f-Src

