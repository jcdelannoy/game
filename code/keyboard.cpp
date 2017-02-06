#include "keyboard.h"
#include <Windows.h>

KeyBoard::KeyBoard()
{
    // inquire -999 to get number of keys
    short numKeys = KeyBoard::getKeyIndex(-999);
    KeyBoard::isPressed = new bool[numKeys];
    KeyBoard::wasPressed = new bool[numKeys];

    for (int i = 0; i < numKeys; i++) {
        KeyBoard::isPressed[i] = FALSE;
        KeyBoard::wasPressed[i] = FALSE;
    }
}

KeyBoard::~KeyBoard()
{
    delete [] KeyBoard::isPressed;
    delete [] KeyBoard::wasPressed;
}

short KeyBoard::getKeyIndex(short keyGLFWid) {
    if (keyGLFWid == -999) 
        return 6; //RETURN NUMBER OF KEYS
    if (keyGLFWid == GLFW_KEY_ESCAPE) 
        return 0;
    if (keyGLFWid == GLFW_KEY_Q) 
        return 1;
    if (keyGLFWid == GLFW_KEY_A) 
        return 2;
    if (keyGLFWid == GLFW_KEY_D) 
        return 3;
    if (keyGLFWid == GLFW_KEY_W)
        return 4;
    if (keyGLFWid == GLFW_KEY_S)
        return 5;

    return -999; //NOT DEFINED
}

void KeyBoard::keyCallback(GLFWwindow* window, int keyGLFWid, int scancode, int action, int mode)
{
    short keyIndex = KeyBoard::getKeyIndex(keyGLFWid); //get keyIndex
    if (keyIndex == -999) return; //NOT DEFINED

    //  update keyState
    KeyBoard::wasPressed[keyIndex] = KeyBoard::isPressed[keyIndex];
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        KeyBoard::isPressed[keyIndex] = TRUE;
    }
    else
    {
        KeyBoard::isPressed[keyIndex] = FALSE;
    }
}

bool KeyBoard::keyIsPressed(short keyGLFWid) {
    short keyIndex = KeyBoard::getKeyIndex(keyGLFWid); //get keyIndex
    return KeyBoard::isPressed[keyIndex];
}

bool KeyBoard::keyWasPressed(short keyGLFWid) {
    short keyIndex = KeyBoard::getKeyIndex(keyGLFWid); //get keyIndex
    return KeyBoard::wasPressed[keyIndex];
}