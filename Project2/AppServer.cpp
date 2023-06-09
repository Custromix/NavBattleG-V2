﻿#include "Utils.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"MaWinClass";

    if (!RegisterClass(&wc)) return FALSE;

    hwnd = CreateWindowA("MaWinClass", "Titre", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hinstance, NULL);
    if (!hwnd) return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);


    // Allouer une console
    AllocConsole();

    // Rediriger la sortie standard vers la console
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    std::cout << "Hello, world!" << std::endl;

    try {
        Server* g_server = new Server(257523, hwnd);

        g_server->Listen();

        g_server->Start();

        g_server->Clear();

    }
    catch (const std::exception& e) {
        // Bloc de code qui sera exécuté en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }


    // Fermer la console
    FreeConsole();

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
/****************************************************************************/

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:

        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}