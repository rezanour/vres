#include <Windows.h>
#include <stdint.h>
#include <assert.h>
#include "../VRES/Include/VRES.h"

// Constants
static const wchar_t ApplicationName[] = L"BasicSample";
static const uint32_t WinWidth = 1280;
static const uint32_t WinHeight = 720;

// Forward declarations
static LRESULT CALLBACK AppWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Entry point
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcx.hInstance = instance;
    wcx.lpfnWndProc = AppWindowProc;
    wcx.lpszClassName = ApplicationName;

    if (RegisterClassEx(&wcx) == INVALID_ATOM)
    {
        assert(false);
        return -1;
    }

    DWORD style = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    RECT rc{ 0, 0, WinWidth, WinHeight };
    AdjustWindowRect(&rc, style, FALSE);

    HWND hwnd = CreateWindow(ApplicationName, ApplicationName, style, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, instance, nullptr);
    if (!hwnd)
    {
        assert(false);
        return -2;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    if (!VRES_Initialize(hwnd))
    {
        assert(false);
        return -3;
    }

    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Idle
        }
    }

    VRES_Shutdown();
    DestroyWindow(hwnd);
    return (int)msg.wParam;
}

LRESULT CALLBACK AppWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_KEYUP:
        if (wParam == VK_ESCAPE)
        {
            // As a convenience, currently accept ESC key to quit
            PostQuitMessage(0);
        }
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
