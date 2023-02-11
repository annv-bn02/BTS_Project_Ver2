cmake_minimum_required(VERSION 3.0.0)
project(uart_frame VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(uart_frame lib/main.cpp lib/serialport.cpp lib/bts_get_message.cpp lib/bts_frame_message.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)