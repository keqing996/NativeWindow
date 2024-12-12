
#include <unordered_map>
#include "NativeWindow/Input/Input.h"

namespace NativeWindow
{
    Input::Input()
    {
        _buttonData.resize(static_cast<int>(ButtonType::Count));
    }

    void Input::ProcessEventQueue()
    {
        static std::unordered_map<ButtonType, bool> lastFrameBtnPressedRecord;

        lastFrameBtnPressedRecord.clear();

        for (const auto& [eventType, eventData] : _eventQueue)
        {
            if (eventType == InputEventType::Button)
            {
                auto& inputData = eventData.button;
                ButtonData& data = GetButton(inputData.button);

                bool oldValue;
                if (lastFrameBtnPressedRecord.find(inputData.button)
                    == lastFrameBtnPressedRecord.end())
                {
                    lastFrameBtnPressedRecord[inputData.button] = inputData.isPress;
                    oldValue = inputData.isPress;
                }
                else
                {
                    oldValue = lastFrameBtnPressedRecord[inputData.button];
                }

                data.pressed = inputData.isPress;
                data.changed = oldValue != inputData.isPress;
            }
        }

        _eventQueue.clear();
    }

    bool Input::IsButtonPressed(ButtonType key) const
    {
        return GetButton(key).pressed;
    }

    bool Input::IsButtonPressedThisFrame(ButtonType key) const
    {
        auto data = GetButton(key);
        return data.pressed && data.changed;
    }

    Input::ButtonData& Input::GetButton(ButtonType key)
    {
        return _buttonData[static_cast<int>(key)];
    }

    const Input::ButtonData& Input::GetButton(ButtonType key) const
    {
        return _buttonData[static_cast<int>(key)];
    }
}
