#include "framework.h"



CClient::CClient(HWND window)
{
    window_ = window;
    pQMM = new QueueMessageManager();

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup a �chou� avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    // Cr�er un socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Erreur de cr�ation du socket : " << WSAGetLastError() << std::endl;
    }



}

bool CClient::Connect(const char ip[], const char port[])
{
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int status = getaddrinfo(ip, port, &hints, &result);
    if (status != 0) {
        std::cout << "Impossible de r�soudre l'adresse IP du serveur : " << gai_strerror(status) << std::endl;
        
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    serverAddr.sin_port = htons(std::stoi(port));

    // Se connecter au serveur
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Impossible de se connecter au serveur : " << WSAGetLastError() << std::endl;
        OutputDebugStringA("PAS SEND BUFFER");

    }
    else {
        std::cout << "C'est bon !" << WSAGetLastError() << std::endl;
    }

    WSAAsyncSelect(clientSocket, window_, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

    SetWindowLongPtr(window_, GWLP_USERDATA, (LONG_PTR)this);

    //OutputDebugStringA("SEND MESSAGE \n");

    return false;
}

void CClient::SendToServer(std::string message)
{
    if (send(clientSocket, message.c_str(), message.length(), 0)) {
        OutputDebugStringA("SEND MESSAGE");
    }

}


LRESULT CALLBACK CClient::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SOCKET Accept;

    switch (uMsg)
    {

    case WM_PAINT:
    {
        break;
    }

    case WM_SOCKET:
    {

        //CClient* pClient = (CClient*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        OutputDebugStringA("SEND MESSAGE");
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
            OutputDebugStringA("SEND MESSAGE");
            /*std::string buffer(1024, 0);
            int num_bytes_received = recv(wParam, &buffer[0], buffer.size(), 0);

            if (num_bytes_received != SOCKET_ERROR)
            {
                OutputDebugStringA("\n");
                OutputDebugStringA(buffer.c_str());
                OutputDebugStringA("\n");
                pServer->ProtocolExecuter(pServer->Parser(buffer));
            }*/

            // Receive data from the socket in wParam

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

void CClient::ProtocolExecuter(std::string)
{
}




