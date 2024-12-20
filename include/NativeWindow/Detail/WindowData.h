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
        bool AddService();

        template<typename T>
        T* GetService();

        const std::vector<Service*>& GetServices();

        void ClearService();

    private:
        Service* GetServiceInternal(ServiceType type);
        void AddServiceInternal(ServiceType type);
        bool CanServiceBeAdded(ServiceType type);

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
    bool WindowData::AddService()
    {
        if (GetService<T>() != nullptr)
            return true;

        // Check all conflicts
        auto serviceType = T::ServiceType();
        if (!CanServiceBeAdded(serviceType))
            return false;

        AddServiceInternal(serviceType);
        return true;
    }

    template<typename T>
    T* WindowData::GetService()
    {
        return reinterpret_cast<T*>(GetServiceInternal(T::ServiceType()));
    }
}