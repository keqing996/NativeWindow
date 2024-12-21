#pragma once

#include "../Service.h"

namespace NativeWindow
{
    class ImGuiService: public Service
    {
    public:
        explicit ImGuiService(void* hWnd);
        ~ImGuiService() override;

    public:
        void ProcessWinMessage(void* hWnd, uint32_t msg, void* wPara, void* lPara) override;
        void BeforeTick() override;
        void AfterTick() override;

    protected:
        // Dpi
        float GetDpiScale();
        // Font
        int GetDefaultFontSize();
        ImFont* CreateImGuiFont(void* fontData, int fontDataSize, int fontSize, bool transferDataOwnership = true);
        ImFont* CreateImGuiFont(const std::string& ttfPath, int fontSize);
    };
}