#pragma once
#include <Windows.h>
class KeyBoard
{
    static const unsigned int numberOfKeys = 256U;
    bool previousKeyboardState[numberOfKeys];
    HKL keyBoardLayoutId;
public:
    KeyBoard();
    ~KeyBoard();

    bool isPressed(char x);
};


