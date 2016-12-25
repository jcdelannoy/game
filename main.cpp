#include <stdio.h>
#include <stdlib.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <Windows.h>
#include <mmsystem.h>

const GLint WIDTH = 640, HEIGHT = 480;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"void main( )\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0 );"
"}";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main( )\n"
"{\n"
"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
"}";

int main()
{
    // init GLFW - an open source, multi-platform library for OpenGL, OpenGL ES and Vulkan dev.
    // It proves an API for creating windows, contexts and surfaces, receiving input and events.
    if (!glfwInit())
    {
        fprintf(stderr, "GLFW failed to initialize.");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);    
    //glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    // init GLEW - OpenGL Extension Wrangler.
    // It provides efficient run-time mechanims for determining which OpenGL extensions are supported on the target platform.
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW.");
        return EXIT_FAILURE;
    }
    glViewport(0, 0, screenWidth, screenHeight);

    // compile vertex shader - handles the processing of individual vertices.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");
        fprintf(stderr, infoLog);
    }

    // setup fragment shader - the pipeline stage after a primitive is rasterized.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
        fprintf(stderr, infoLog);
    }

    // link shaders.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED");
        fprintf(stderr, infoLog);
    }

    // no longer need the vertex & fragment shaders, as they are now part of the compiled program.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // define a triangle.
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.0f, 0.5f, 0.0f // top middle
    };

    // generate Vertex Buffer Object and Vertex Array Object.
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid * ) 0);
    glEnableVertexAttribArray(0);
    
    // cleanup.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // main loop.
	PlaySound(TEXT("./audioFiles/testViolin.wav"), NULL, SND_FILENAME);
    while (!glfwWindowShouldClose(window))
    {
        // check if any events have been activated and call handlers.
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // swap screen buffers.
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // clear any resources allocated by GLFW.
    glfwTerminate();
    return EXIT_SUCCESS;
}

