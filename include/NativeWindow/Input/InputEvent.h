
#pragma once

#include <utility>
#include "InputEnum.h"

namespace NativeWindow
{
    enum class InputEventType
    {
        MouseMove,
        MouseButton,
        MouseWheel,
        KeyboardButton
    };

    struct MouseMoveData
    {
        std::pair<int, int> position;
    };

    struct MouseButtonData
    {
        MouseButton button;
        bool isPress;
    };

    struct MouseWheelData
    {
        float delta;
        bool isUp;
    };

    struct KeyboardButtonData
    {
        Key button;
        bool isPress;
    };

    union InputEventData
    {
        MouseMoveData mouseMove;
        MouseButtonData mouseButton;
        MouseWheelData mouseWheel;
        KeyboardButtonData keyboard;
    };

    struct InputEvent
    {
        InputEventType eventType;
        InputEventData data;
    };

}