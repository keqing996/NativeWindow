#pragma once

namespace NativeWindow
{
    enum ServiceIndex: int
    {
        ServiceIndex_Input = 0,
        ServiceIndex_OpenGL,
        ServiceIndex_ImGui,
        ServiceIndex_Count
    };

    class IService
    {
    public:
        virtual ~IService() = default;

    public:
        virtual void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara) = 0;
        virtual void Loop() = 0;
    };

    template<ServiceIndex Index>
    class ServiceIndexWithIndex: public IService
    {
    public:
        int static ServiceIndex()
        {
            return Index;
        }
    };

}