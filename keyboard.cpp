#include "keyboard.h"
#include <Windows.h>

KeyBoard::KeyBoard()
{
    KeyBoard::keyBoardLayoutId = GetKeyboardLayout(0);
}

KeyBoard::~KeyBoard()
{
}
static const unsigned int NumberOfKeys = 256U;

bool previousKeyboardState[NumberOfKeys];


bool KeyBoard::isPressed(char x)
{
    short keyId;
    keyId = VkKeyScanEx(x, KeyBoard::keyBoardLayoutId);
    // is_pressed will be true if the key is currently being held down
    bool justPressed = (GetAsyncKeyState(keyId) & 0x8001) != 0;
    return (justPressed);
}