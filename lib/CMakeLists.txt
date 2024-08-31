# ----- GLAD Configuration -----
add_library(glad STATIC GLAD/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/GLAD/include)

# ----- GLFW Configuration -----
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/GLFW/lib/libglfw3dll.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/GLFW/include
)

# ----- Create Alias for GLFW -----
add_library(glfw::glfw ALIAS glfw)
