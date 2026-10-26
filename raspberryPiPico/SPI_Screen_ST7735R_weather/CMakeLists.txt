cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

set(PICO_BOARD pico2_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(SPI_Screen_ST7735R_weather C CXX ASM)

pico_sdk_init()

add_executable(SPI_Screen_ST7735R_weather
    SPI_Screen_ST7735R_weather.c
)

target_link_libraries(SPI_Screen_ST7735R_weather 
    pico_stdlib
    hardware_spi
    pico_cyw43_arch_lwip_poll
    pico_lwip
)

# --- ADD THESE LINES ---
pico_enable_stdio_usb(SPI_Screen_ST7735R_weather 1)
pico_enable_stdio_uart(SPI_Screen_ST7735R_weather 0)

target_include_directories(SPI_Screen_ST7735R_weather PRIVATE
    .
)

pico_add_extra_outputs(SPI_Screen_ST7735R_weather)