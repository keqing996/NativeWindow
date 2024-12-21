#pragma once

#include <array>
#include "ImGuiService.h"

namespace NativeWindow
{
    class ImGuiOpenGLService: public ImGuiService
    {
    public:
        explicit ImGuiOpenGLService(void* hWnd);
        ~ImGuiOpenGLService() override;

    public:
        void BeforeTick() override;
        void AfterTick() override;

        void SetClearColor(float r, float g, float b, float a);

    private:
        std::array<float, 4> _clearColor = { 0.75f, 0.75f, 0.75f, 1.00f };
    };
}