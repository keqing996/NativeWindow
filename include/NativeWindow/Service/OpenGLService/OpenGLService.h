#pragma once

#include "../Service.h"

namespace NativeWindow
{
    class OpenGLService: public Service, public ServiceTypeGetter<ServiceType::OpenGL>
    {
    public:
        explicit OpenGLService(void* hWnd);
        ~OpenGLService() override;

    public:


    private:
        void* _hDeviceHandle = nullptr;
        void* _hGLContext = nullptr;
    };
}