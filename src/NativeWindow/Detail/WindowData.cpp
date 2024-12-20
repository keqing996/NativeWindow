#include "NativeWindow/Detail/WindowData.h"

namespace NativeWindow
{
    WindowData::WindowData(void* windowHandle)
        : _hWindow(windowHandle)
    {
    }

    WindowData::~WindowData()
    {
        auto itr = _servicesInCreationOrder.rbegin();
        for (; itr != _servicesInCreationOrder.rend(); ++itr)
            delete *itr;

        _servicesInCreationOrder.clear();
        _serviceMap.clear();
    }

    void* WindowData::GetWindowHandle() const
    {
        return _hWindow;
    }

    const std::vector<Service*>& WindowData::GetServices()
    {
        return _servicesInCreationOrder;
    }

    Service* WindowData::AddService(ServiceType type)
    {
        auto itr = _serviceMap.find(type);
        if (itr != _serviceMap.end())
            return itr->second;

        auto pDependentService = Service::GetServiceDependent(type);
        if (pDependentService != nullptr)
        {
            for (auto dependentServiceType: *pDependentService)
                AddService(dependentServiceType);
        }

        Service* service = Service::CreateService(_hWindow, type);
        _serviceMap[type] = service;
        _servicesInCreationOrder.push_back(service);

        return service;
    }
}
