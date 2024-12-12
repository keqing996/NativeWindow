#pragma once

namespace NativeWindow
{
    enum class ButtonType: int
    {
        /* Mouse */
        MouseLeft = 0,
        MouseMiddle,
        MouseRight,
        MouseXButton4,
        MouseXButton5,
        /* Keyboard A-Z */
        KeyboardA, KeyboardB, KeyboardC, KeyboardD,
        KeyboardE, KeyboardF, KeyboardG, KeyboardH,
        KeyboardI, KeyboardJ, KeyboardK, KeyboardL,
        KeyboardM, KeyboardN, KeyboardO, KeyboardP,
        KeyboardQ, KeyboardR, KeyboardS, KeyboardT,
        KeyboardU, KeyboardV, KeyboardW, KeyboardX,
        KeyboardY, KeyboardZ,
        /* Keyboard F1-F15 */
        KeyboardF1,  KeyboardF2,  KeyboardF3,
        KeyboardF4,  KeyboardF5,  KeyboardF6,
        KeyboardF7,  KeyboardF8,  KeyboardF9,
        KeyboardF10, KeyboardF11, KeyboardF12,
        KeyboardF13, KeyboardF14, KeyboardF15,
        /* Keyboard Arrow */
        KeyboardArrowUp,
        KeyboardArrowDown,
        KeyboardArrowLeft,
        KeyboardArrowRight,
        /* Keyboard Num */
        KeyboardNum0, KeyboardNum1, KeyboardNum2, KeyboardNum3,
        KeyboardNum4, KeyboardNum5, KeyboardNum6, KeyboardNum7,
        KeyboardNum8, KeyboardNum9,
        /* Keyboard NumPad */
        KeyboardNumPad0, KeyboardNumPad1, KeyboardNumPad2,
        KeyboardNumPad3, KeyboardNumPad4, KeyboardNumPad5,
        KeyboardNumPad6, KeyboardNumPad7, KeyboardNumPad8,
        KeyboardNumPad9, KeyboardNumPadMinus, KeyboardNumPadAdd,
        KeyboardNumPadMultiply, KeyboardNumPadDivide,
        /* Keyboard Other */
        KeyboardEscape,
        KeyboardTab,
        KeyboardLControl,
        KeyboardLAlt,
        KeyboardLShift,
        KeyboardLSystem,
        KeyboardRControl,
        KeyboardRAlt,
        KeyboardRShift,
        KeyboardRSystem,
        KeyboardMenu,
        KeyboardLBracket,
        KeyboardRBracket,
        KeyboardSpace,
        KeyboardEnter,
        KeyboardBackspace,
        KeyboardPageUp,
        KeyboardPageDown,
        KeyboardHome,
        KeyboardEnd,
        KeyboardDelete,
        KeyboardInsert,
        KeyboardMinus,
        KeyboardEqual,
        KeyboardPause,
        KeyboardSemicolon,      /* ; */
        KeyboardComma,          /* , */
        KeyboardPeriod,         /* . */
        KeyboardApostrophe,     /* ' */
        KeyboardSlash,          /* / */
        KeyboardBackslash,      /* \ */
        KeyboardGrave,          /* ` */
        Unknown,
        Count
    };
}
