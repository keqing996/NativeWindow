
#pragma once

#include <cstdint>
#include "ServiceType.h"

namespace NativeWindow
{
    class IService
    {
    public:
        virtual ~IService() = default;
        virtual void WindowEventProcessInternal(uint32_t message, void* wpara, void* lpara) = 0;
    };

    template<ServiceType type>
    class ServiceWithSlot: IService
    {
    public:
        static ServiceType GetType()
        {
            return type;
        }
    };
}