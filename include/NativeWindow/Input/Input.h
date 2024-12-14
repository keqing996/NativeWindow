
#pragma once

#include <vector>
#include "InputEvent.h"

namespace NativeWindow
{
    class Input
    {
    public:
        explicit Input(void* hWnd);

        void BeforeWinMsgLoop();
        void ProcessWinMessage(uint32_t msg, void* wpara, void* lpara);
        void AfterWinMsgLoop();

        bool IsButtonPressed(ButtonType key) const;
        bool IsButtonPressedThisFrame(ButtonType key) const;
        std::pair<int, int> GetMousePosition() const;
        float GetMouseWheel() const;

    private:
        struct ButtonData
        {
            bool pressed;
            bool changed;
        };

        void ProcessEventQueue();

        ButtonData& GetButton(ButtonType key);
        const ButtonData& GetButton(ButtonType key) const;

        ButtonType WinVirtualKeyToButtonType(void* wpara, void* lpara);

    private:
        void* _hWnd;
        std::vector<InputEvent> _eventQueue;

        std::pair<int, int> _mousePos;
        float _mouseWheel;
        std::vector<ButtonData> _buttonData;

    };
}