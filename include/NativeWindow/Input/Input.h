
#pragma once

#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "InputEvent.h"

namespace NativeWindow
{
    class Input
    {
    public:
        Input();

        void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara);
        void ProcessEventQueue();

        bool IsButtonPressed(ButtonType key) const;
        std::pair<int, int> GetMousePosition() const;
        float GetMouseWheel() const;

        bool GetIsAutoRepeat() const;
        void SetIsAutoRepeat(bool autoRepeat);

        void SetCallbackOnMouseMove(const std::function<void(std::pair<int, int>, std::pair<int, int>)>& fun);
        void SetCallbackOnMouseWheel(const std::function<void(float)>& fun);
        void SetCallbackOnButtonPressed(const std::function<void(ButtonType)>& fun);
        void SetCallbackOnButtonReleased(const std::function<void(ButtonType)>& fun);

    private:
        ButtonType WinVirtualKeyToButtonType(void* wpara, void* lpara);

    private:
        std::vector<InputEvent> _eventQueue;

        std::pair<int, int> _mousePos;
        float _mouseWheel;

        bool _enableAutoRepeat = true;
        std::unordered_set<ButtonType> _pressedButton;

        std::function<void(std::pair<int, int>, std::pair<int, int>)> _onMouseMove = nullptr;
        std::function<void(float)> _onMouseWheel = nullptr;
        std::function<void(ButtonType)> _onButtonPressed = nullptr;
        std::function<void(ButtonType)> _onButtonReleased = nullptr;
    };
}