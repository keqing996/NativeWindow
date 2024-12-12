
#pragma once

#include <vector>
#include "InputEvent.h"

namespace NativeWindow
{
    class Input
    {
    public:
        Input();

        void ProcessEventQueue();

        bool IsKeyPressed(Key key) const;

        bool IsKeyPressedThisFrame(Key key) const;

    private:
        struct KeyboardData
        {
            bool pressed;
            bool changed;
        };

        KeyboardData& GetKey(Key key);

        const KeyboardData& GetKey(Key key) const;

    private:
        std::vector<InputEvent> _eventQueue;

        std::vector<KeyboardData> _keyboard;

    };
}