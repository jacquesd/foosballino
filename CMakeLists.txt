cmake_minimum_required(VERSION 3.2)
project(foosballino)

include(CMakeListsPrivate.txt)

add_definitions(-DF_CPU=84000000L)
add_definitions(-DUSBCON)
add_definitions(-DUSB_MANUFACTURER="PlatformIO")
add_definitions(-Dprintf=iprintf)
add_definitions(-D__SAM3X8E__)
add_definitions(-DARDUINO_SAM_DUE)
add_definitions(-DARDUINO_ARCH_SAM)
add_definitions(-DUSB_VID=0x2341)
add_definitions(-DUSB_PID=0x003e)
add_definitions(-DUSB_PRODUCT="Arduino Due")
add_definitions(-DARDUINO=10607)
add_definitions(-DPLATFORMIO=020806)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

#
# To enable code auto-completion, please specify path
# to main source file (*.c, *.cpp) and uncomment line below
#
# add_executable(foosballino src/main_change_me.cpp)
