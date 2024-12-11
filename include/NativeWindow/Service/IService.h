
#pragma once

#include <cstdint>

namespace NativeWindow
{
    class IService
    {
    public:
        virtual void WindowEventProcessInternal(uint32_t message, void* wpara, void* lpara) = 0;
    };
}