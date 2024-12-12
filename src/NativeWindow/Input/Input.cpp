
#include <unordered_map>
#include "NativeWindow/Input/Input.h"

namespace NativeWindow
{
    Input::Input()
    {
        _keyboard.resize(static_cast<int>(Key::Count));
    }

    void Input::ProcessEventQueue()
    {
        static std::unordered_map<Key, bool> lastFrameKeyboardPressedRecord;

        lastFrameKeyboardPressedRecord.clear();

        for (const auto& [eventType, eventData] : _eventQueue)
        {
            if (eventType == InputEventType::KeyboardButton)
            {
                auto& inputData = eventData.keyboard;
                KeyboardData& data = GetKey(inputData.button);

                bool oldValue;
                if (lastFrameKeyboardPressedRecord.find(inputData.button)
                    == lastFrameKeyboardPressedRecord.end())
                {
                    lastFrameKeyboardPressedRecord[inputData.button] = inputData.isPress;
                    oldValue = inputData.isPress;
                }
                else
                {
                    oldValue = lastFrameKeyboardPressedRecord[inputData.button];
                }

                data.pressed = inputData.isPress;
                data.changed = oldValue != inputData.isPress;
            }
        }

        _eventQueue.clear();
    }

    bool Input::IsKeyPressed(Key key) const
    {
        return GetKey(key).pressed;
    }

    bool Input::IsKeyPressedThisFrame(Key key) const
    {
        auto data = GetKey(key);
        return data.pressed && data.changed;
    }

    Input::KeyboardData& Input::GetKey(Key key)
    {
        return _keyboard[static_cast<int>(key)];
    }

    const Input::KeyboardData& Input::GetKey(Key key) const
    {
        return _keyboard[static_cast<int>(key)];
    }
}
