
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

        bool IsButtonPressed(ButtonType key) const;
        bool IsButtonPressedThisFrame(ButtonType key) const;

    private:
        struct ButtonData
        {
            bool pressed;
            bool changed;
        };

        ButtonData& GetButton(ButtonType key);
        const ButtonData& GetButton(ButtonType key) const;

    private:
        std::vector<InputEvent> _eventQueue;

        std::vector<ButtonData> _buttonData;

    };
}