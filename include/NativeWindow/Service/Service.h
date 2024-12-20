#pragma once

#include <vector>
#include <cstdint>

namespace NativeWindow
{
    enum class ServiceType: int
    {
        Input,
        OpenGL,
        ImGuiOpenGL,
    };

    template<ServiceType Type>
    class ServiceTypeGetter
    {
    public:
        static ServiceType ServiceType()
        {
            return Type;
        }
    };

    class Service
    {
    public:
        virtual ~Service() = default;

    public:
        virtual void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara) = 0;
        virtual void BeforeTick();
        virtual void AfterTick();
        virtual void FinishLoop();

    public:
        static const std::vector<ServiceType>* GetServiceDependent(ServiceType type);
        static const std::vector<ServiceType>* GetServiceConflict(ServiceType type);
        static Service* CreateService(void* hWnd, ServiceType type);

    protected:
        explicit Service(void* hWnd);

        void* _hWnd;
    };

}