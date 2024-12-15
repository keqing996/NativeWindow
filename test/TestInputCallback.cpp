#include <iostream>
#include <NativeWindow/Window.h>

int main()
{
    NativeWindow::Window window;

    window.GetInput().SetCallbackOnMouseMove([](std::pair<int, int> source, std::pair<int, int> target) -> void
    {
        std::cout << "[MouseMove]   (" << source.first << ", " << source.second << ") -> ("
            << target.first << ", " << target.second << ")" << std::endl;
    });

    window.GetInput().SetCallbackOnMouseWheel([](float delta) -> void
    {
        std::cout << "[MouseWheel]   (" << delta << ")" << std::endl;
    });

    window.GetInput().SetCallbackOnButtonPressed([](NativeWindow::ButtonType btn) -> void
    {
        std::cout << "[BtnPressed]  " << NativeWindow::ButtonTypeUtility::GetName(btn) << std::endl;
    });

    window.GetInput().SetCallbackOnButtonReleased([](NativeWindow::ButtonType btn) -> void
    {
        std::cout << "[BtnRelease]  " << NativeWindow::ButtonTypeUtility::GetName(btn) << std::endl;
    });

    window.Create(800, 600, "Test", NativeWindow::WindowStyle::DefaultStyle());

    while (true)
    {
        bool finish;
        window.EventLoop(&finish);
        if (finish)
            break;

        if (window.GetInput().IsButtonPressed(NativeWindow::ButtonType::KeyboardU))
        {
            bool currentCursorVisible = window.IsCursorVisible();
            window.SetCursorVisible(!currentCursorVisible);
        }
    }

    system("pause");

    return 0;
}