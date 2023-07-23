# freertos/lwip template // cmake template  taken from
# pico-examples/pico_w/wifi/freertos/iperf

# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "d:/RaspberryPiPico2/pico-sdk")

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


# ///////////////////////////////////////////////////// freertos

set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/freertos)
include(FreeRTOS_Kernel_import.cmake)

# ///////////////////////////////


project(picow4wd_server C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.2.1



#target_include_directories(picow4wd_server PRIVATE src )
#target_include_directories(picow4wd_server ${CMAKE_CURRENT_LIST_DIR}/src )

#add_subdirectory(src)
#include_directories(${MyProject_SOURCE_DIR}/src)

add_executable(picow4wd_server 
	src/entry.c 
	src/panic.c
	src/task_blinker.c
	src/task_console.c
	src/task_network.c
	src/task_heartbeat.c
	src/task_demux.c
	src/task_drive.c
	src/task_lights.c
	src/hardware_drive.c
	src/hardware_lights.c
)


target_include_directories(picow4wd_server PRIVATE
	freertos/include
	freertos/portable/ThirdParty/GCC/RP2040/include/
)

# don't want NO_SYS (generally this would be in your lwipopts.h)
target_compile_definitions(picow4wd_server PRIVATE NO_SYS=0 )

pico_set_program_name(picow4wd_server "picow4wd_server")
pico_set_program_version(picow4wd_server "0.2.1")

pico_enable_stdio_uart(picow4wd_server 1)
pico_enable_stdio_usb(picow4wd_server 1)

# Add the standard include files to the build
target_include_directories(picow4wd_server PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(picow4wd_server
    pico_stdlib
    hardware_spi
    hardware_timer
    hardware_clocks
    hardware_pwm
	pico_cyw43_arch_lwip_sys_freertos
    FreeRTOS-Kernel-Heap4
)

pico_add_extra_outputs(picow4wd_server)

