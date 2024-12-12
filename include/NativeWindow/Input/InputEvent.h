
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

    struct MouseMoveEventData
    {
        std::pair<int, int> position;
    };

    struct MouseButtonEventData
    {
        MouseButton button;
        bool isPress;
    };

    struct MouseWheelEventData
    {
        float delta;
        bool isUp;
    };

    struct KeyboardEventData
    {
        Key button;
        bool isPress;
    };

    union InputEventData
    {
        MouseMoveEventData mouseMove;
        MouseButtonEventData mouseButton;
        MouseWheelEventData mouseWheel;
        KeyboardEventData keyboard;
    };

    struct InputEvent
    {
        InputEventType eventType;
        InputEventData data;
    };

}