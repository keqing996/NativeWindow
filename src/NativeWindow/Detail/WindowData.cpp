#include "NativeWindow/Detail/WindowData.h"

namespace NativeWindow
{
    WindowData::WindowData(void* windowHandle)
        : _hWindow(windowHandle)
    {
        _services.resize(ServiceIndex_Count);
        std::fill(_services.begin(), _services.end(), nullptr);
    }

    WindowData::~WindowData()
    {
        for (auto p: _services)
        {
            if (p != nullptr)
                delete p;
        }

        _services.clear();
    }

    void* WindowData::GetWindowHandle() const
    {
        return _hWindow;
    }

    const std::vector<Service*>& WindowData::GetServices()
    {
        return _services;
    }
}
