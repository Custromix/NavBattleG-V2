#include "framework.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Static_ThreadProc(LPVOID lpParameter);


MSG msg;


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    WNDCLASS wc;


    DWORD idThread;
    HANDLE hThread = CreateThread(NULL, 0, Static_ThreadProc, NULL, 0, &idThread);


    if (hThread == NULL)
    {
        OutputDebugString(L"erreur de création du thread");
        return 1;
    }

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

    App* BATTLENAVALMUTLI = new App();

    SetApp(BATTLENAVALMUTLI);

    try {
        BATTLENAVALMUTLI->Init();
        BATTLENAVALMUTLI->Start();

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

    // Fermer la console
    FreeConsole();



    return msg.wParam;
}
/****************************************************************************/


DWORD WINAPI Static_ThreadProc(LPVOID lpParameter) {

    HWND window2;
    HINSTANCE hinstance = GetModuleHandle(NULL);;

    window2 = CreateWindow(L"MaWinClass", L"Titre", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hinstance, NULL);


    CClient* cli = new CClient(window2);

    cli->Connect("127.0.0.1", "27523");

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
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
            OutputDebugStringA("SEND MESSAGE \n");


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