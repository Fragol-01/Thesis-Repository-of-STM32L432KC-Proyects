# Minimal toolchain file for ARM Cortex-M devices
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g3 -DDEBUG -DSTM32L432xx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity --specs=nano.specs")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT}")
set(CMAKE_ASM_FLAGS_INIT "${CMAKE_C_FLAGS_INIT}")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-specs=rdimon.specs -lc -lm -lrdimon")

# Otras configuraciones que necesites para tu proyecto
