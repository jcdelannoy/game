#pragma once
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class KeyBoard
{
    bool* isPressed;
    bool* wasPressed;

public:
    KeyBoard();
    ~KeyBoard();

    short getKeyIndex(short keyGLFWid);
    void keyCallback(GLFWwindow* window, int keyGLFWid, int scancode, int action, int mode);
    bool KeyBoard::keyIsPressed(short keyGLFWid);
    bool KeyBoard::keyWasPressed(short keyGLFWid);
};



