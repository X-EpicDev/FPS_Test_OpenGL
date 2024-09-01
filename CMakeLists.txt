# ----- "Minimum CMake Version" -----
cmake_minimum_required(VERSION 3.10)

# ----- "Project Definition" -----
project(AHHHHHH)

# ----- Set project source directory -----
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# ----- "C++ Standard" -----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----- "Executable Target" -----
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp)

# ----- "Libaries" -----
#GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")

#GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")