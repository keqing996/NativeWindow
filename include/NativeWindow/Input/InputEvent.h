
#pragma once

#include <utility>
#include "InputEnum.h"

namespace NativeWindow
{
    enum class InputEventType
    {
        MouseMove,
        MouseWheel,
        Button,
    };

    struct MouseMoveEventData
    {
        std::pair<int, int> position;
    };

    struct MouseWheelEventData
    {
        float delta;
    };

    struct ButtonData
    {
        ButtonType button;
        bool isPress;
    };

    union InputEventData
    {
        MouseMoveEventData mouseMove;
        MouseWheelEventData mouseWheel;
        ButtonData button;
    };

    struct InputEvent
    {
        InputEventType eventType;
        InputEventData data;
    };

}