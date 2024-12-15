
#pragma once

#include <functional>
#include <unordered_set>
#include <vector>
#include "InputEvent.h"

namespace NativeWindow
{
    class Input
    {
    public:
        Input();

        void BeforeWinMsgLoop();
        void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara);
        void AfterWinMsgLoop();

        bool IsButtonPressed(ButtonType key) const;
        bool IsButtonPressedThisFrame(ButtonType key) const;
        std::pair<int, int> GetMousePosition() const;
        float GetMouseWheel() const;

        void SetCallbackOnMouseMove(const std::function<void(std::pair<int, int>, std::pair<int, int>)>& fun);
        void SetCallbackOnMouseWheel(const std::function<void(float)>& fun);
        void SetCallbackOnButtonPressed(const std::function<void(ButtonType)>& fun);
        void SetCallbackOnButtonReleased(const std::function<void(ButtonType)>& fun);

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
        std::vector<InputEvent> _eventQueue;

        std::pair<int, int> _mousePosLastFrame;
        std::pair<int, int> _mousePos;
        float _mouseWheel;
        std::unordered_set<ButtonType> _thisFrameChangedButtons;
        std::vector<ButtonData> _buttonData;

        std::function<void(std::pair<int, int>, std::pair<int, int>)> _onMouseMove = nullptr;
        std::function<void(float)> _onMouseWheel = nullptr;
        std::function<void(ButtonType)> _onButtonPressed = nullptr;
        std::function<void(ButtonType)> _onButtonReleased = nullptr;
    };
}