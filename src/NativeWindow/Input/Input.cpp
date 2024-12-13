#include <unordered_map>
#include "NativeWindow/Utility/WindowsInclude.h"
#include "NativeWindow/Input/Input.h"

namespace NativeWindow
{
    Input::Input()
    {
        _buttonData.resize(static_cast<int>(ButtonType::Count));
    }

    void Input::ProcessWinMessage(uint32_t msg, void* wpara, void* lpara)
    {
        WPARAM wParam = reinterpret_cast<WPARAM>(wpara);
        LPARAM lParam = reinterpret_cast<LPARAM>(lpara);
        switch (msg)
        {
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            {
                const bool pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
                auto button = WinVirtualKeyToButtonType(wpara, lpara);

                InputEvent inputEvent{};
                inputEvent.eventType = InputEventType::Button;
                inputEvent.data.button.button = button;
                inputEvent.data.button.isPress = pressed;

                _eventQueue.emplace_back(inputEvent);
                
                break;
            }
        }
    }

    void Input::ProcessEventQueue()
    {
        static std::unordered_map<ButtonType, bool> lastFrameBtnPressedRecord;

        lastFrameBtnPressedRecord.clear();

        for (const auto& [eventType, eventData]: _eventQueue)
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
                } else
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

    ButtonType Input::WinVirtualKeyToButtonType(void* wpara, void* lpara)
    {
        WPARAM wParam = reinterpret_cast<WPARAM>(wpara);
        LPARAM lParam = reinterpret_cast<LPARAM>(lpara);
        if ((wParam == VK_RETURN) && (HIWORD(lParam) & KF_EXTENDED))
            return ButtonType::KeyboardNumPadEnter;

        switch (wParam)
        {
            /* Keyboard A-Z */
            case 'A':       return ButtonType::KeyboardA;
            case 'B':       return ButtonType::KeyboardB;
            case 'C':       return ButtonType::KeyboardC;
            case 'D':       return ButtonType::KeyboardD;
            case 'E':       return ButtonType::KeyboardE;
            case 'F':       return ButtonType::KeyboardF;
            case 'G':       return ButtonType::KeyboardG;
            case 'H':       return ButtonType::KeyboardH;
            case 'I':       return ButtonType::KeyboardI;
            case 'J':       return ButtonType::KeyboardJ;
            case 'K':       return ButtonType::KeyboardK;
            case 'L':       return ButtonType::KeyboardL;
            case 'M':       return ButtonType::KeyboardM;
            case 'N':       return ButtonType::KeyboardN;
            case 'O':       return ButtonType::KeyboardO;
            case 'P':       return ButtonType::KeyboardP;
            case 'Q':       return ButtonType::KeyboardQ;
            case 'R':       return ButtonType::KeyboardR;
            case 'S':       return ButtonType::KeyboardS;
            case 'T':       return ButtonType::KeyboardT;
            case 'U':       return ButtonType::KeyboardU;
            case 'V':       return ButtonType::KeyboardV;
            case 'W':       return ButtonType::KeyboardW;
            case 'X':       return ButtonType::KeyboardX;
            case 'Y':       return ButtonType::KeyboardY;
            case 'Z':       return ButtonType::KeyboardZ;
            /* Keyboard Num */
            case '0':       return ButtonType::KeyboardNum0;
            case '1':       return ButtonType::KeyboardNum1;
            case '2':       return ButtonType::KeyboardNum2;
            case '3':       return ButtonType::KeyboardNum3;
            case '4':       return ButtonType::KeyboardNum4;
            case '5':       return ButtonType::KeyboardNum5;
            case '6':       return ButtonType::KeyboardNum6;
            case '7':       return ButtonType::KeyboardNum7;
            case '8':       return ButtonType::KeyboardNum8;
            case '9':       return ButtonType::KeyboardNum9;
            /* Keyboard F1-F24 */
            case VK_F1:     return ButtonType::KeyboardF1;
            case VK_F2:     return ButtonType::KeyboardF2;
            case VK_F3:     return ButtonType::KeyboardF3;
            case VK_F4:     return ButtonType::KeyboardF4;
            case VK_F5:     return ButtonType::KeyboardF5;
            case VK_F6:     return ButtonType::KeyboardF6;
            case VK_F7:     return ButtonType::KeyboardF7;
            case VK_F8:     return ButtonType::KeyboardF8;
            case VK_F9:     return ButtonType::KeyboardF9;
            case VK_F10:    return ButtonType::KeyboardF10;
            case VK_F11:    return ButtonType::KeyboardF11;
            case VK_F12:    return ButtonType::KeyboardF12;
            case VK_F13:    return ButtonType::KeyboardF13;
            case VK_F14:    return ButtonType::KeyboardF14;
            case VK_F15:    return ButtonType::KeyboardF15;
            case VK_F16:    return ButtonType::KeyboardF16;
            case VK_F17:    return ButtonType::KeyboardF17;
            case VK_F18:    return ButtonType::KeyboardF18;
            case VK_F19:    return ButtonType::KeyboardF19;
            case VK_F20:    return ButtonType::KeyboardF20;
            case VK_F21:    return ButtonType::KeyboardF21;
            case VK_F22:    return ButtonType::KeyboardF22;
            case VK_F23:    return ButtonType::KeyboardF23;
            case VK_F24:    return ButtonType::KeyboardF24;
            /* Keyboard Navigation */
            case VK_LEFT:       return ButtonType::KeyboardArrowLeft;
            case VK_RIGHT:      return ButtonType::KeyboardArrowRight;
            case VK_UP:         return ButtonType::KeyboardArrowUp;
            case VK_DOWN:       return ButtonType::KeyboardArrowDown;
            /* Keyboard NumPad */
            case VK_NUMPAD0:    return ButtonType::KeyboardNumPad0;
            case VK_NUMPAD1:    return ButtonType::KeyboardNumPad1;
            case VK_NUMPAD2:    return ButtonType::KeyboardNumPad2;
            case VK_NUMPAD3:    return ButtonType::KeyboardNumPad3;
            case VK_NUMPAD4:    return ButtonType::KeyboardNumPad4;
            case VK_NUMPAD5:    return ButtonType::KeyboardNumPad5;
            case VK_NUMPAD6:    return ButtonType::KeyboardNumPad6;
            case VK_NUMPAD7:    return ButtonType::KeyboardNumPad7;
            case VK_NUMPAD8:    return ButtonType::KeyboardNumPad8;
            case VK_NUMPAD9:    return ButtonType::KeyboardNumPad9;
            case VK_ADD:        return ButtonType::KeyboardNumPadAdd;
            case VK_DECIMAL:    return ButtonType::KeyboardNumPadDecimal;
            case VK_DIVIDE:     return ButtonType::KeyboardNumPadDivide;
            case VK_MULTIPLY:   return ButtonType::KeyboardNumPadMultiply;
            case VK_SUBTRACT:   return ButtonType::KeyboardNumPadMinus;
            case VK_NUMLOCK:    return ButtonType::KeyboardNumPadLock;
            /* Keyboard Control */
            case VK_ESCAPE:     return ButtonType::KeyboardEscape;
            case VK_TAB:        return ButtonType::KeyboardTab;
            case VK_CAPITAL:    return ButtonType::KeyboardCapital;
            case VK_LSHIFT:     return ButtonType::KeyboardLeftShift;
            case VK_LCONTROL:   return ButtonType::KeyboardLeftCtrl;
            case VK_LWIN:       return ButtonType::KeyboardLeftWindows;
            case VK_LMENU:      return ButtonType::KeyboardLeftAlt;
            case VK_SPACE:      return ButtonType::KeyboardSpace;
            case VK_RMENU:      return ButtonType::KeyboardRightAlt;
            case VK_RWIN:       return ButtonType::KeyboardRightWindows;
            case VK_RCONTROL:   return ButtonType::KeyboardRightCtrl;
            case VK_RSHIFT:     return ButtonType::KeyboardRightShift;
            case VK_BACK:       return ButtonType::KeyboardBackspace;
            case VK_RETURN:
            {
                // Enter key and numpad enter key are same virtual key "VK_RETURN",
                // so we should use "KF_EXTENDED" to distinct them.
                if (HIWORD(lParam) & KF_EXTENDED)
                    return ButtonType::KeyboardNumPadEnter;
                else
                    return ButtonType::KeyboardEnter;
            }
            /* Keyboard Edit */
            case VK_INSERT:     return ButtonType::KeyboardInsert;
            case VK_DELETE:     return ButtonType::KeyboardDelete;
            case VK_PRIOR:      return ButtonType::KeyboardPageUp;
            case VK_NEXT:       return ButtonType::KeyboardPageDown;
            case VK_HOME:       return ButtonType::KeyboardHome;
            case VK_END:        return ButtonType::KeyboardEnd;
            /* Keyboard Sign */
            case VK_OEM_COMMA:  return ButtonType::KeyboardComma;
            case VK_OEM_PERIOD: return ButtonType::KeyboardPeriod;
            case VK_OEM_2:      return ButtonType::KeyboardSlash;
            case VK_OEM_1:      return ButtonType::KeyboardSemicolon;
            case VK_OEM_7:      return ButtonType::KeyboardApostrophe;
            case VK_OEM_4:      return ButtonType::KeyboardLeftBracket;
            case VK_OEM_6:      return ButtonType::KeyboardRightBracket;
            case VK_OEM_5:      return ButtonType::KeyboardBackslash;
            case VK_OEM_3:      return ButtonType::KeyboardGraveAccent;
            case VK_OEM_MINUS:  return ButtonType::KeyboardMinus;
            case VK_OEM_PLUS:   return ButtonType::KeyboardEqual;
            /* Keyboard Other */
            case VK_PAUSE:              return ButtonType::KeyboardPause;
            case VK_SNAPSHOT:           return ButtonType::KeyboardPrintScreen;
            case VK_SCROLL:             return ButtonType::KeyboardScrollLock;
            case VK_VOLUME_MUTE:        return ButtonType::KeyboardVolumeMute;
            case VK_VOLUME_UP:          return ButtonType::KeyboardVolumeUp;
            case VK_VOLUME_DOWN:        return ButtonType::KeyboardVolumeDown;
            case VK_MEDIA_PLAY_PAUSE:   return ButtonType::KeyboardMediaPlayPause;
            case VK_MEDIA_STOP:         return ButtonType::KeyboardMediaStop;
            case VK_MEDIA_PREV_TRACK:   return ButtonType::KeyboardMediaPrev;
            case VK_MEDIA_NEXT_TRACK:   return ButtonType::KeyboardMediaNext;
            /* Finish */
            default:        return ButtonType::Unknown;
        }
    }
}
