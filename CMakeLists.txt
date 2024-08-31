cmake_minimum_required(VERSION 3.10)
project(YourProject)

# ----- C++ Standard Configuration -----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- Add Subdirectory for Libraries -----
add_subdirectory(lib)

# ----- Add Executable -----
add_executable(YourProject src/main.cpp)

# ----- Include Directories for Libraries -----
target_include_directories(YourProject PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/GLFW/include
        ${CMAKE_SOURCE_DIR}/lib/GLAD/include
)

# ----- Link Libraries to Executable -----
target_link_libraries(YourProject PRIVATE
        glfw
        glad
)

# ----- Set Location of DLLs -----
set_target_properties(YourProject PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ----- Copy GLFW DLL to Output Directory -----
add_custom_command(TARGET YourProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/lib/GLFW/lib/glfw3.dll
        $<TARGET_FILE_DIR:YourProject>
)
