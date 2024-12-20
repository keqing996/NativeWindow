#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <optional>
#include <memory>

#include "Detail/WindowStyle.h"
#include "Detail/WindowData.h"
#include "NativeWindow/Utility/NonCopyable.h"

namespace NativeWindow
{
    class NativeWindowUtility;

    class Window final: Utility::NonCopyable
    {
    public:
        Window();
        ~Window();

    public:
        /// Create window instance.
        /// @param width Window width.
        /// @param height Window height.
        /// @param title Window title in UTF8.
        /// @param style Window style.
        /// @return Create success.
        bool Create(int width, int height, const std::string& title, WindowStyle style);

        /// Destroy window instance.
        void Destroy();

        /// Check is window instance created.
        bool IsWindowValid() const;

        /// Window main loop.
        /// @param loopFunction called every frame.
        void Loop(const std::function<void()>& loopFunction);

        /// Get native window's size(client area, without borders, caption bar, etc.).
        std::pair<int, int> GetSize();

        /// Set native window's size.
        void SetSize(int width, int height);

        /// Get native window's position in screen.
        std::pair<int, int> GetPosition();

        /// Set native window's position in screen.
        void SetPosition(int x, int y);

        /// Get native window handle, which is HWND in this case.
        void* GetSystemHandle() const;

        /// Set icon of window through bytes in memory.
        /// @param width Icon width.
        /// @param height Icon height.
        /// @param pixels Icon bytes data in RGBA.
        void SetIcon(unsigned int width, unsigned int height, const std::byte* pixels);

        /// Set icon of window through windows resource id.
        void SetIcon(int iconResId);

        /// Set window title in UTF8.
        void SetTitle(const std::string& title);

        /// Set window visible.
        void SetWindowVisible(bool show);

        /// Get is cursor visible.
        bool IsCursorVisible() const;

        /// Set cursor visible.
        void SetCursorVisible(bool show);

        /// Is cursor limited in window client area.
        bool IsCursorLimitedInWindow() const;

        /// Set cursor limited in window client area.
        void SetCursorLimitedInWindow(bool capture);

        /// Get is cursor inside window now (frame not included).
        bool IsCursorInsideWindow() const;

        /// Called when window is created.
        void SetCallbackOnWindowCreated(const std::function<void()>& callback);

        /// Called when window is trying to close, return true to let
        /// window close, return false to refuse window to close.
        void SetCallbackOnWindowTryToClose(const std::function<bool()>& callback);

        /// Called when window is closed.
        void SetCallbackOnWindowClosed(const std::function<void()>& callback);

        /// Called when window is about to be destroyed, at this moment, WM_DESTROY
        /// is not sent to window yet, and all resources (icon, or something) are still
        /// held by window.
        void SetCallbackOnWindowPreDestroyed(const std::function<void()>& callback);

        /// Called when window is already destroyed, at this moment, WM_DESTROY is
        /// already received, all resources are released, window is closed.
        void SetCallbackOnWindowPostDestroyed(const std::function<void()>& callback);

        /// Called when windows messages received.
        ///
        /// - uint32_t: message Windows message.
        /// - void*: wpara WPARAM.
        /// - void*: lpara LPARAM.
        /// - int*: result If block original message process, return value of message.
        ///
        /// Returned bool: Should block original message process, should be false in most cases.
        void SetCallbackOnWindowMessagePreProcess(const std::function<bool(uint32_t, void*, void*, int*)>& callback);

        /// Called when window received WM_MOVE
        ///
        /// - int: left up corner x.
        /// - int: left up corner y.
        void SetCallbackOnWindowMoved(const std::function<void(int,int)>& callback);

        /// Called when window received WM_SIZE
        /// - int: new size width.
        /// - int: new size height.
        void SetCallbackOnWindowResize(const std::function<void(int, int)>& callback);

        /// Called when window get or lost focus,
        /// true for enter focus and false for lose focus.
        void SetCallbackOnWindowFocusChanged(const std::function<void(bool)>& callback);

        /// Called when cursor enters or leaves window, true for
        /// enters window and false for leaves window.
        void SetCallbackOnWindowCursorEnteredOrLeaved(const std::function<void(bool)>& callback);

        /// Called when cursor's visibility changes, true for shown and false for hided.
        void SetCallbackOnWindowCursorVisibleChanged(const std::function<void(bool)>& callback);

        template<typename T>
        T* AddService();

        template<typename T>
        T* GetService();

    private:
        void SetTrackMouseLeave(bool enable);
        void OnWindowClose();
        void OnWindowPreDestroy();
        void OnWindowPostDestroy();
        int WindowEventProcess(uint32_t message, void* wpara, void* lpara);
        void WindowEventProcessInternal(uint32_t message, void* wpara, void* lpara);
        void SetCursorLimitedInWindowInternal(bool doCapture);
        bool CalculateMouseInsideWindow() const;

    private:
        friend NativeWindowUtility;

    private:
        std::unique_ptr<WindowData> _pWindowState = nullptr;

        std::function<void()> _onWindowCreated = nullptr;
        std::function<void(int,int)> _onWindowMoved = nullptr;
        std::function<bool(uint32_t, void*, void*, int*)> _onWindowMessagePreProcess = nullptr;
        std::function<bool()> _onWindowTryToClose = nullptr;
        std::function<void()> _onWindowClosed = nullptr;
        std::function<void()> _onWindowPreDestroyed = nullptr;
        std::function<void()> _onWindowPostDestroyed = nullptr;
        std::function<void(int,int)> _onWindowResize = nullptr;
        std::function<void(bool)> _onWindowFocusChanged = nullptr;
        std::function<void(bool)> _onWindowCursorEnteredOrLeaved = nullptr;
        std::function<void(bool)> _onWindowCursorVisibleChanged = nullptr;

    private:
        static void RegisterWindowClass();
        static void UnRegisterWindowClass();
    };

    template<typename T>
    T* Window::AddService()
    {
        if (_pWindowState == nullptr)
            return nullptr;

        return _pWindowState->AddService<T>();
    }

    template<typename T>
    T* Window::GetService()
    {
        if (_pWindowState == nullptr)
            return nullptr;

        return _pWindowState->GetService<T>();
    }
}
