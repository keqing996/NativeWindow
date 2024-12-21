
#include "NativeWindow/Service/OpenGLService/OpenGLService.h"
#include <glad/gl.h>
#include <glad/wgl.h>

#pragma comment(lib, "opengl32.lib")

namespace NativeWindow
{
    OpenGLService::OpenGLService(void* hWnd)
        : Service(hWnd)
    {
        _hDeviceHandle = ::GetDC(static_cast<HWND>(_hWnd));

        PIXELFORMATDESCRIPTOR pfd =
                {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
            PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
            32,                   // Color depth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                   // Number of bits for the depth buffer
            8,                    // Number of bits for the stencil buffer
            0,                    // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        int letWindowsChooseThisPixelFormat = ::ChoosePixelFormat(static_cast<HDC>(_hDeviceHandle), &pfd);
        ::SetPixelFormat(static_cast<HDC>(_hDeviceHandle), letWindowsChooseThisPixelFormat, &pfd);

        _hGLContext = ::wglCreateContext(static_cast<HDC>(_hDeviceHandle));
        ::wglMakeCurrent(static_cast<HDC>(_hDeviceHandle), static_cast<HGLRC>(_hGLContext));

        // Loading GL function must after gl context make current.
        ::gladLoaderLoadGL();
        ::gladLoaderLoadWGL(static_cast<HDC>(_hDeviceHandle)); // for wgl extension function

        // Init with vysnc true
        SetVSync(true);
    }

    OpenGLService::~OpenGLService()
    {
        HWND hWnd = static_cast<HWND>(_hWnd);

        if (_hDeviceHandle)
        {
            ::wglMakeCurrent(static_cast<HDC>(_hDeviceHandle), nullptr);
            ::ReleaseDC(hWnd, static_cast<HDC>(_hDeviceHandle));
            _hDeviceHandle = nullptr;
        }

        if (_hGLContext)
        {
            ::wglDeleteContext(static_cast<HGLRC>(_hGLContext));
            _hGLContext = nullptr;
        }
    }

    void OpenGLService::FinishLoop()
    {
        ::SwapBuffers(static_cast<HDC>(_hGLContext));
    }

    void OpenGLService::SetVSync(bool enable)
    {
        _enableVSync = enable;

        // wglSwapInterval is from WGL_EXT_swap_control, so maybe null
        if (wglSwapIntervalEXT != nullptr)
            ::wglSwapIntervalEXT(_enableVSync);
    }

}
