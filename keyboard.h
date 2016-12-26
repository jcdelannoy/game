#pragma once
#include <Windows.h>

class keyBoard
{
    HKL keyBoardLayoutId;
public:
    keyBoard();
    ~keyBoard();
    void getLayout();
    bool isPressed(char x);
};


