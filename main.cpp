#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// misc.
#include "shader.h"

// audio headers
#include <Windows.h>
#include <mmsystem.h>

// keyboard inputs
#include "keyboard.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    // init GLFW.
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // init GLEW.
    // use modern techniques for managing OpenGL functionality.
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW.");
        return EXIT_FAILURE;
    }
    glViewport(0, 0, screenWidth, screenHeight);

    // compile the default shader.
    Shader defaultShader("default.vs", "default.frag");

    // setup vertex data and attribute pointers.
    GLfloat vertices[] =
    {
        // positions            // colors
        0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,   0.0f, // bottom right
        -0.5f,  -0.5f,  0.0f,   0.0f,   1.0f,   0.0f,// bottom left
        0.0f,   0.5f,   0.0f,   0.0f,   0.0f,   1.0f // top left
    };

    // generate Vertex Buffer Object and Vertex Array Object and Element Buffer Object.
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(0); // location = 0

    // color attribute.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // location = 1
    
    // cleanup.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    KeyBoard keyboard;

    // main loop.
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the vertices.q
        defaultShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    
        // swap screen buffers.
        glfwSwapBuffers(window);

        if (keyboard.isPressed('q'))
        {
            PlaySound(TEXT("./audioFiles/testViolin.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

