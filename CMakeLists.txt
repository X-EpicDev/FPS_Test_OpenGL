cmake_minimum_required(VERSION 3.14)
project(opengltriangle)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable(${PROJECT_NAME} src/main.cpp)