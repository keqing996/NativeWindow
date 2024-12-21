#pragma once

#include <array>
#include "../Service.h"

namespace NativeWindow
{
    class OpenGLService: public Service, public ServiceTypeGetter<ServiceType::OpenGL>
    {
    public:
        explicit OpenGLService(Window* pWindow);
        ~OpenGLService() override;

    public:
        void FinishLoop() override;
        void SetVSync(bool enable);

    private:
        bool _enableVSync = true;
        void* _hDeviceHandle = nullptr;
        void* _hGLContext = nullptr;
    };
}