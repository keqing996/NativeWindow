
#pragma once

#include "InputEvent.h"

namespace NativeWindow
{
    class Input
    {
    public:
        enum ButtonState
        {

            Press,
            Hold,
            Release,
        };

    private:
        bool _keyboardAutoRepeat = true;

    };
}