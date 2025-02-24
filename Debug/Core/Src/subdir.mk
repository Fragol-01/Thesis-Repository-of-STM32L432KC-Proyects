################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_dma_test.c \
../Core/Src/adc_dma_tim_test.c \
../Core/Src/adc_test.c \
../Core/Src/exti_PB_TEST.c \
../Core/Src/main.c \
../Core/Src/printf_redirect.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/adc_dma_test.o \
./Core/Src/adc_dma_tim_test.o \
./Core/Src/adc_test.o \
./Core/Src/exti_PB_TEST.o \
./Core/Src/main.o \
./Core/Src/printf_redirect.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/adc_dma_test.d \
./Core/Src/adc_dma_tim_test.d \
./Core/Src/adc_test.d \
./Core/Src/exti_PB_TEST.d \
./Core/Src/main.d \
./Core/Src/printf_redirect.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L432xx -c -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Core/Inc" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/CMSIS/Include" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Peripherals/Inc" -I"C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Application/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_dma_test.cyclo ./Core/Src/adc_dma_test.d ./Core/Src/adc_dma_test.o ./Core/Src/adc_dma_test.su ./Core/Src/adc_dma_tim_test.cyclo ./Core/Src/adc_dma_tim_test.d ./Core/Src/adc_dma_tim_test.o ./Core/Src/adc_dma_tim_test.su ./Core/Src/adc_test.cyclo ./Core/Src/adc_test.d ./Core/Src/adc_test.o ./Core/Src/adc_test.su ./Core/Src/exti_PB_TEST.cyclo ./Core/Src/exti_PB_TEST.d ./Core/Src/exti_PB_TEST.o ./Core/Src/exti_PB_TEST.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/printf_redirect.cyclo ./Core/Src/printf_redirect.d ./Core/Src/printf_redirect.o ./Core/Src/printf_redirect.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

