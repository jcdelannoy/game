#include "keyboard.h"
#include <Windows.h>

KeyBoard::KeyBoard()
{
    KeyBoard::keyBoardLayoutId = GetKeyboardLayout(0);
}

KeyBoard::~KeyBoard()
{
}

bool KeyBoard::isPressed(char x)
{
    short keyId;
    keyId = VkKeyScanEx(x, KeyBoard::keyBoardLayoutId);
    // is_pressed will be true if the key is currently being held down
    return (GetAsyncKeyState(keyId) & 0x8000) != 0;
}