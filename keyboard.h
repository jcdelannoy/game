#pragma once
#include <Windows.h>

class KeyBoard
{
    HKL keyBoardLayoutId;
public:
    KeyBoard();
    ~KeyBoard();

    bool isPressed(char x);
};


