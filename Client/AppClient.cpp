#include "framework.h"

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



    try {
        CClient* cli = new CClient(hwnd);

        cli->Connect("127.0.0.1", "27523");

        //cli->Main();

    }
    catch (const std::exception& e) {
        // Bloc de code qui sera exécuté en cas d'exception
        // ...
        std::cout << "Exception : " << e.what() << std::endl;
    }


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

    case WM_PAINT:
    {
        break;
    }

    case WM_SOCKET:
    {

        CClient* pClient = (CClient*)GetWindowLongPtr(hwnd, GWLP_USERDATA);


        if (WSAGETSELECTERROR(lParam))
        {
            closesocket((SOCKET)wParam);
            break;
        }

        // Determine what event occurred on the socket

        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_READ:
        {

            std::string buffer(1024, 0);
            int num_bytes_received = recv(wParam, &buffer[0], buffer.size(), 0);

            if (num_bytes_received != SOCKET_ERROR)
            {
                OutputDebugStringA("\n");
                OutputDebugStringA(buffer.c_str());
                OutputDebugStringA("\n");
                pClient->ProtocolExecuter(buffer);
            }

            // Receive data from the socket in wParam

            break;
        }
        case FD_WRITE:
        {

            if (!pClient->pQMM->IsEmpty())
            {
                OutputDebugStringA("SEND MESSAGE \n");
                std::string message = pClient->pQMM->DequeueMessage();
                pClient->SendToServer(message);
            }

            // The socket in wParam is ready for sending data
            break;

        }
        case FD_CLOSE:
        {
            // The connection is now closed

            closesocket((SOCKET)wParam);

            break;
        }
        }

        break;
    }
    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}