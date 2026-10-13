cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake) # OTETAAN PICO-SDK KÄYTTÖÖN
pico_sdk_init()
project(counter C CXX ASM) # PROJEKTIN NIMI COUNTER
add_executable(counter main.c) # KÄYTETÄÄN MAIN.C-TIEDOSTOA
target_link_libraries(counter pico_stdlib) # TARVITTAVAT KIRJASTOT

# TULOSTUS
pico_enable_stdio_usb(counter 1)
pico_enable_stdio_uart(counter 1)

# .elf ULOS
pico_add_extra_outputs(counter)
