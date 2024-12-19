#pragma once

#include <cstdint>

namespace NativeWindow
{
    enum ServiceIndex: int
    {
        ServiceIndex_Input = 0,
        ServiceIndex_OpenGL,
        ServiceIndex_ImGui,
        ServiceIndex_Count
    };

    class Service
    {
    public:
        virtual ~Service() = default;

    public:
        void SetWindowHandle(void* hWnd);

    public:
        virtual void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara) = 0;
        virtual void Loop() = 0;

    protected:
        void* _hWnd = nullptr;;
    };

    template<ServiceIndex Index>
    class ServiceIndexWithIndex: public Service
    {
    public:
        int static ServiceIndex()
        {
            return Index;
        }
    };

}