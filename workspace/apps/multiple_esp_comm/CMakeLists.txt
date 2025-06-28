cmake_minimum_required(VERSION 3.22.0)

set(ZEPHYR_EXTRA_MODULES "${CMAKE_SOURCE_DIR}/../../modules/display_brightness")
set(ZEPHYR_EXTRA_MODULES "${CMAKE_SOURCE_DIR}/../../modules/number_of_leds")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(adc_demo)

include_directories(include)

target_sources(app PRIVATE
               src/main.c
               src/uart_comm.c
               src/gpio_get.c)