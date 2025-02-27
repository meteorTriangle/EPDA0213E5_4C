cmake_minimum_required(VERSION 3.18)

project(EPD C CXX ASM)

add_library(EPD STATIC
    epd_lib.cpp
)

target_link_libraries(EPD 
    pico_stdlib
    hardware_spi
)

target_include_directories(EPD PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
