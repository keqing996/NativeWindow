
#include <unordered_map>
#include "NativeWindow/Service/Service.h"
#include "NativeWindow/Service/InputService/InputService.h"

namespace NativeWindow
{
    static std::unordered_map<ServiceType, std::vector<ServiceType>> gServiceDependentMap = {
        { ServiceType::ImGuiOpenGL, { ServiceType::OpenGL } },
    };

    static std::unordered_map<ServiceType, std::vector<ServiceType>> gConflictMap = {
    };

    Service::Service(void* hWnd)
        : _hWnd(hWnd)
    {
    }

    void Service::BeforeTick()
    {
    }

    void Service::AfterTick()
    {
    }

    void Service::FinishLoop()
    {
    }

    const std::vector<ServiceType>* Service::GetServiceDependent(ServiceType type)
    {
        auto itr = gServiceDependentMap.find(type);
        if (itr != gServiceDependentMap.end())
            return &itr->second;

        return nullptr;
    }

    const std::vector<ServiceType>* Service::GetServiceConflict(ServiceType type)
    {
        auto itr = gConflictMap.find(type);
        if (itr != gConflictMap.end())
            return &itr->second;

        return nullptr;
    }

    Service* Service::CreateService(void* hWnd, ServiceType type)
    {
        switch (type)
        {
            case ServiceType::Input:
                return new InputService(hWnd);
            default:
                return nullptr;
        }
    }
}
