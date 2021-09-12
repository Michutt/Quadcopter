cmake_minimum_required(VERSION 3.16)

include ($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(Quadcopter C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

pico_sdk_init()

add_executable(${PROJECT_NAME}
    src/main.c
    lib/NRF24L01.c
    src/logic/motors.c
)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_spi
    hardware_gpio
    hardware_pwm
)