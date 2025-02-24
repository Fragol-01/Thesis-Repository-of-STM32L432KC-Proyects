cmake_minimum_required(VERSION 3.10)

# Establece el nombre del sistema y procesador
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

# Especifica las herramientas de compilación
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

project(BEGINNER_STM32L432KC C ASM)

# Estándares de C y C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# Opciones de compilación:
#    -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#    -std=gnu11 -g3 -DDEBUG -DSTM32L432xx
#    -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs
set(DEVICE_FLAGS   "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(DEBUG_FLAGS    "-g3 -DDEBUG -DSTM32L432xx")
set(OTHER_FLAGS    "-O0 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs")

set(CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} ${DEVICE_FLAGS} ${DEBUG_FLAGS} ${OTHER_FLAGS} -std=gnu11")
set(CMAKE_ASM_FLAGS  "${CMAKE_ASM_FLAGS} ${DEVICE_FLAGS} ${DEBUG_FLAGS} ${OTHER_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${DEVICE_FLAGS} ${DEBUG_FLAGS} ${OTHER_FLAGS}")

# Agrega el ejecutable; se asume que los archivos fuente (.c) se encuentran en las siguientes carpetas.
# Ajusta las rutas según la organización de tu proyecto.
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Peripherals/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Application/*.c"
)

# Excluir syscalls.c de los archivos fuente
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/syscalls.c")

add_executable(BEGINNER_STM32L432KC ${SRC_FILES})

# Directorios de inclusión (usa rutas absolutas conforme a lo que indicaste)
target_include_directories(BEGINNER_STM32L432KC PUBLIC
    "C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Core/Inc"
    "C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/CMSIS/Include"
    "C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Peripherals/Inc"
    "C:/Users/DANNY/STM32CubeIDE/BEGINNER_STM32L432KC/Application/Inc"
)

# Opciones de enlazado. En este ejemplo se enlazan las bibliotecas básicas.
target_link_libraries(BEGINNER_STM32L432KC PUBLIC
    -Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end-group
)

# Propiedades del target: genera un archivo con extensión .elf
set_target_properties(BEGINNER_STM32L432KC PROPERTIES SUFFIX ".elf")

# Generación de archivos HEX y BIN post-compilación usando arm-none-eabi-objcopy
find_program(OBJCOPY arm-none-eabi-objcopy)
if(NOT OBJCOPY)
    message(FATAL_ERROR "arm-none-eabi-objcopy no se encontró!")
endif()

add_custom_command(TARGET BEGINNER_STM32L432KC POST_BUILD
    COMMAND ${OBJCOPY} -O ihex $<TARGET_FILE:BEGINNER_STM32L432KC> ${CMAKE_CURRENT_BINARY_DIR}/BEGINNER_STM32L432KC.hex
    COMMAND ${OBJCOPY} -O binary $<TARGET_FILE:BEGINNER_STM32L432KC> ${CMAKE_CURRENT_BINARY_DIR}/BEGINNER_STM32L432KC.bin
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=rdimon.specs -lc -lm -lrdimon")
