// GLEW, GLFW, GLM
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "game.h"
#include "resourceManager.h"
#include "keyboard.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 1024;
const GLuint SCREEN_HEIGHT = 768;
Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

HANDLE loadResource(LPSTR lpName) 
{
    HANDLE hRes;
    hRes = LoadResource(NULL, FindResource(NULL, lpName, "WAVE"));
    if (hRes == NULL)
        return NULL;
    return hRes;
}

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    // define the keyboard.
    KeyBoard* keyboard = new KeyBoard();
    glfwSetWindowUserPointer(window, keyboard);
    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // glewInit() always causes an innocuous error.

    // opengl configuation.
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.Init();
    game.state = GAME_ACTIVE;

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        // jc(todo): replace this with a constant update system.
        GLfloat currentFrame = ((GLfloat)glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // process user input.
        deltaTime = 0.002f;
        game.ProcessInput(deltaTime, keyboard);

        // update game.
        game.Update(deltaTime);

        // render.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        glfwSwapBuffers(window);

        // keyboard processing.
        if (keyboard->keyIsPressed(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        if (keyboard->keyIsPressed(GLFW_KEY_Q) && !(keyboard->keyWasPressed(GLFW_KEY_Q))) 
        {
            PlaySound(TEXT("./data/audioFiles/testViolin.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }

    ResourceManager::Clear();
    glfwTerminate();
    return EXIT_SUCCESS;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
    KeyBoard* keyboard = reinterpret_cast<KeyBoard*>(glfwGetWindowUserPointer(window));
    keyboard->keyCallback(window, key, scancode, action, mode);
}

//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    }
//
//    if (key >= 0 && key < 1024)
//    {
//        if (action == GLFW_PRESS)
//        {
//            game.keys[key] = GL_TRUE;
//        }
//        else if (action == GLFW_RELEASE)
//        {
//            game.keys[key] = GL_FALSE;
//        }
//    }
//}

