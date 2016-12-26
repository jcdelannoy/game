#include "keyboard.h"
#include <Windows.h>

keyBoard::keyBoard()
{
}

void keyBoard::getLayout()
{
    keyBoard::keyBoardLayoutId = GetKeyboardLayout(0);
}


keyBoard::~keyBoard()
{
}

bool keyBoard::isPressed(char x)
{
    short keyId;
    keyId = VkKeyScanEx(x, keyBoard::keyBoardLayoutId);
    // is_pressed will be true if the key is currently being held down
    return (GetAsyncKeyState(keyId) & 0x8000) != 0;
}