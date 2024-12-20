#pragma once

#include <unordered_map>
#include <vector>

#include "../Service/Service.h"

namespace NativeWindow
{
    class WindowData
    {
    public:
        explicit WindowData(void* windowHandle);
        ~WindowData();

    public:
        void* GetWindowHandle() const;

        template<typename T>
        T GetWindowHandle() const;

        template<typename T>
        T* AddService();

        template<typename T>
        T* GetService();

        const std::vector<Service*>& GetServices();

    public:
        void* hIcon = nullptr;
        void* hCursor = nullptr;

        bool cursorVisible = true;
        bool cursorLimitedInWindow = false;
        bool cursorInsideWindow = false;

        int lastWidth = 0;
        int lastHeight = 0;

    private:
        void* _hWindow = nullptr;
        std::vector<Service*> _servicesInCreationOrder;
        std::unordered_map<ServiceType, Service*> _serviceMap;
    };

    template<typename T>
    T WindowData::GetWindowHandle() const
    {
        return reinterpret_cast<T>(GetWindowHandle());
    }

    template<typename T>
    T* WindowData::AddService()
    {
        ServiceType type = T::ServiceType();
        auto itr = _serviceMap.find(type);
        if (itr != _serviceMap.end())
            return itr->second;

        Service* service = Service::CreateService(_hWindow, type);
        _serviceMap[type] = service;
        return service;
    }

    template<typename T>
    T* WindowData::GetService()
    {
        return reinterpret_cast<T*>(_services[T::ServiceIndex()]);
    }
}