project(rc2017_1v1 C)
cmake_minimum_required(VERSION 3.6)

#set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE USER_GOMI_MAIN_SOURCES "UP_TestAll/User_main/main_gomi.c")
file(GLOB_RECURSE USER_HGW_MAIN_SOURCES "UP_TestAll/User_main/main_hgw.c")
file(GLOB_RECURSE USER_CZY_MAIN_SOURCES "UP_TestAll/User_main/main_czy.c")

file(GLOB_RECURSE USER_UTILS_SOURCES "UP_TestAll/Utils/*.c")
file(GLOB_RECURSE UPLIB_SOURCES "UP_TestAll/UpLib/*.c")

add_library(UPLIB ${UPLIB_SOURCES})
add_library(USERLIB ${USER_UTILS_SOURCES})

include_directories(UP_TestAll)
include_directories(UpLib)
include_directories(UpLib/STM32Lib)
include_directories(UP_TestAll/Utils)

add_definitions(-DSTM32F303xE)
add_definitions(-DSTM32F10X_HD)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUG_ON)
else()
    add_definitions(-DDEBUG_OFF)
endif()

add_executable(${PROJECT_NAME}_gomi.elf ${USER_GOMI_MAIN_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}_gomi.elf UPLIB USERLIB)

set(HEX_FILE ${PROJECT_NAME}_gomi.hex)
set(BIN_FILE ${PROJECT_NAME}_gomi.bin)
add_custom_command(TARGET ${PROJECT_NAME}_gomi.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}_gomi.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}_gomi.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

add_executable(${PROJECT_NAME}_hgw.elf ${USER_HGW_MAIN_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}_hgw.elf UPLIB USERLIB)

set(HEX_FILE ${PROJECT_NAME}_hgw.hex)
set(BIN_FILE ${PROJECT_NAME}_hgw.bin)
add_custom_command(TARGET ${PROJECT_NAME}_hgw.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}_hgw.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}_hgw.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

add_executable(${PROJECT_NAME}_czy.elf ${USER_CZY_MAIN_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}_czy.elf UPLIB USERLIB)

set(HEX_FILE ${PROJECT_NAME}_czy.hex)
set(BIN_FILE ${PROJECT_NAME}_czy.bin)
add_custom_command(TARGET ${PROJECT_NAME}_czy.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}_czy.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}_czy.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
