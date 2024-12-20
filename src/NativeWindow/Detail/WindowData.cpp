#include <functional>
#include <unordered_set>
#include "NativeWindow/Detail/WindowData.h"

namespace NativeWindow
{
    WindowData::WindowData(void* windowHandle)
        : _hWindow(windowHandle)
    {
    }

    WindowData::~WindowData()
    {
        ClearService();
    }

    void* WindowData::GetWindowHandle() const
    {
        return _hWindow;
    }

    const std::vector<Service*>& WindowData::GetServices()
    {
        return _servicesInCreationOrder;
    }

    void WindowData::ClearService()
    {
        auto itr = _servicesInCreationOrder.rbegin();
        for (; itr != _servicesInCreationOrder.rend(); ++itr)
            delete *itr;

        _servicesInCreationOrder.clear();
        _serviceMap.clear();
    }

    Service* WindowData::GetServiceInternal(ServiceType type)
    {
        auto itr = _serviceMap.find(type);
        if (itr == _serviceMap.end())
            return nullptr;

        return itr->second;
    }

    void WindowData::AddServiceInternal(ServiceType type)
    {
        auto itr = _serviceMap.find(type);
        if (itr != _serviceMap.end())
            return;

        auto pDependentService = Service::GetServiceDependent(type);
        if (pDependentService != nullptr)
        {
            for (auto dependentServiceType: *pDependentService)
                AddServiceInternal(dependentServiceType);
        }

        Service* service = Service::CreateService(_hWindow, type);
        _serviceMap[type] = service;
        _servicesInCreationOrder.push_back(service);
    }

    bool WindowData::CanServiceBeAdded(ServiceType type)
    {
        std::unordered_set<ServiceType> tempSet;

        std::function<void(ServiceType)> CollectConflict = [&](ServiceType type)
        {
            auto pConflictServices = Service::GetServiceConflict(type);
            if (pConflictServices != nullptr)
            {
                for (auto conflictServiceType: *pConflictServices)
                {
                    tempSet.insert(conflictServiceType);
                    CollectConflict(conflictServiceType);
                }
            }
        };

        CollectConflict(type);

        for (auto conflictType: tempSet)
        {
            if (GetServiceInternal(conflictType) != nullptr)
                return false;
        }

        return true;
    }
}
