################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/adc.c \
../Peripherals/Src/exti.c \
../Peripherals/Src/gpio.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/tim.c \
../Peripherals/Src/usart.c 

OBJS += \
./Peripherals/Src/adc.o \
./Peripherals/Src/exti.o \
./Peripherals/Src/gpio.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/tim.o \
./Peripherals/Src/usart.o 

C_DEPS += \
./Peripherals/Src/adc.d \
./Peripherals/Src/exti.d \
./Peripherals/Src/gpio.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/tim.d \
./Peripherals/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o Peripherals/Src/%.su Peripherals/Src/%.cyclo: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L432xx -c -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Core/Inc" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/CMSIS/Include" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Peripherals/Inc" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Application/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/adc.cyclo ./Peripherals/Src/adc.d ./Peripherals/Src/adc.o ./Peripherals/Src/adc.su ./Peripherals/Src/exti.cyclo ./Peripherals/Src/exti.d ./Peripherals/Src/exti.o ./Peripherals/Src/exti.su ./Peripherals/Src/gpio.cyclo ./Peripherals/Src/gpio.d ./Peripherals/Src/gpio.o ./Peripherals/Src/gpio.su ./Peripherals/Src/rcc.cyclo ./Peripherals/Src/rcc.d ./Peripherals/Src/rcc.o ./Peripherals/Src/rcc.su ./Peripherals/Src/tim.cyclo ./Peripherals/Src/tim.d ./Peripherals/Src/tim.o ./Peripherals/Src/tim.su ./Peripherals/Src/usart.cyclo ./Peripherals/Src/usart.d ./Peripherals/Src/usart.o ./Peripherals/Src/usart.su

.PHONY: clean-Peripherals-2f-Src

