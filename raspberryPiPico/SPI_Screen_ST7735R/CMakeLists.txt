cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(SPI_Screen_ST7735R C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable matching your source file
add_executable(SPI_Screen_ST7735R
    SPI_Screen_ST7735R.c
)

# Pull in standard libraries and hardware SPI
target_link_libraries(SPI_Screen_ST7735R 
    pico_stdlib
    hardware_spi
)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(SPI_Screen_ST7735R pico_cyw43_arch_none)
endif()

# Create map/bin/hex file etc.
pico_add_extra_outputs(SPI_Screen_ST7735R)