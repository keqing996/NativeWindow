#pragma once

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
        std::vector<Service*> _services;
    };

    template<typename T>
    T WindowData::GetWindowHandle() const
    {
        return reinterpret_cast<T>(GetWindowHandle());
    }

    template<typename T>
    T* WindowData::AddService()
    {
        int index = T::ServiceIndex();
        if (_services[index] == nullptr)
        {
            T* service = new T();
            service->SetWindowHandle(_hWindow);
            _services[index] = service;
            return service;
        }

        return reinterpret_cast<T*>(_services[index]);
    }

    template<typename T>
    T* WindowData::GetService()
    {
        return reinterpret_cast<T*>(_services[T::ServiceIndex()]);
    }
}