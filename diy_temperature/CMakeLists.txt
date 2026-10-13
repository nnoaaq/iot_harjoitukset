cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico2_w)
include(pico_sdk_import.cmake) # OTETAAN PICO-SDK KÄYTTÖÖN
pico_sdk_init()
project(diy_temperature C CXX ASM) # PROJEKTIN NIMI diy_temperature
add_executable(diy_temperature main.c) # KÄYTETÄÄN MAIN.C-TIEDOSTOA
target_link_libraries(diy_temperature pico_stdlib hardware_adc) # TARVITTAVAT KIRJASTOT

# TULOSTUS
pico_enable_stdio_usb(diy_temperature 1)
pico_enable_stdio_uart(diy_temperature 0)

# .utf2 ULOS
pico_add_extra_outputs(diy_temperature)
