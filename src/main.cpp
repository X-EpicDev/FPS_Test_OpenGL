#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>  // <-- Include this for std::vector

namespace std {
    // Function to handle window resizing
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

// Function to process input
    void processInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

// Function to update vertices and indices
    void updateBufferData(unsigned int VBO, unsigned int EBO, const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    int main() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }

        // Configure GLFW for OpenGL version 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        GLFWwindow *window = glfwCreateWindow(800, 600, "Editable Triangle Example", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Set the viewport
        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Define the vertex shader
        const char *vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )glsl";

        // Define the fragment shader
        const char *fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )glsl";

        // Compile the vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Compile the fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Link shaders into a shader program
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Delete the shader objects after linking them into the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Define the vertices and indices for the triangle
        std::vector<float> vertices = {
                // positions
                -0.5f, -0.5f, 0.0f, // bottom left
                0.5f, -0.5f, 0.0f, // bottom right
                0.0f, 0.5f, 0.0f  // top center
        };

        std::vector<unsigned int> indices = {
                0, 1, 2 // triangle
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the Vertex Array Object first
        glBindVertexArray(VAO);

        // Update the vertex and index buffer data
        updateBufferData(VBO, EBO, vertices, indices);

        // Specify the format of the vertex input
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        // Unbind the buffer and the VAO (optional)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Render loop
        while (!glfwWindowShouldClose(window)) {
            // Input
            processInput(window);

            // Render
            glClear(GL_COLOR_BUFFER_BIT);

            // Bind the VAO and draw the triangle using the EBO
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

            // Swap buffers and poll IO events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        glfwTerminate();
        return 0;
    }
}
