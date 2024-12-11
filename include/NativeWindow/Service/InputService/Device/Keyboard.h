
#pragma once

#include "Key.h"

namespace NativeWindow
{
    class Keyboard
    {
    public:
        static bool IsKeyPressed(Key key);
        static int KeyCodeToWinVirtualKey(Key key);
        static Key WinVirtualKeyToKeyCode(int virtualKey, void* lParam);
    };
}