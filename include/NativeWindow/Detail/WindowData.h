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

    private:
        Service* AddService(ServiceType type);

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
        Service* result = AddService(T::ServiceType());
        return reinterpret_cast<T*>(result);
    }

    template<typename T>
    T* WindowData::GetService()
    {
        auto itr = _serviceMap.find(T::ServiceType());
        if (itr == _serviceMap.end())
            return nullptr;

        return reinterpret_cast<T*>(*itr);
    }
}