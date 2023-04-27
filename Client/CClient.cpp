#include "framework.h"
#include <Ws2tcpip.h>
#include <conio.h>
CClient::CClient(HWND window)
{
    window_ = window;
    pQMM = new QueueMessageManager();

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup a échoué avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    // Créer un socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
    }

    WSAAsyncSelect(clientSocket, window, WM_SOCKET, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
}

CClient::~CClient()
{
}

void CClient::Stop() 
{
    closesocket(clientSocket);
    WSACleanup();
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
        std::cout << "Impossible de résoudre l'adresse IP du serveur : " << gai_strerror(status) << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    serverAddr.sin_port = htons(std::stoi(port));

    // Se connecter au serveur
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Impossible de se connecter au serveur : " << WSAGetLastError() << std::endl;
        return false;
    }
    
    return true;    
}

void CClient::SendToServer(std::string message)
{
    if (send(clientSocket, message.c_str(), message.length(), 0)) {
        std::cout << "Données envoyées : " << message << std::endl;
    }
    else
        std::cout << "Données pas envoyé : " << std::endl;

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
        CClient* pClient = (CClient*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        OutputDebugStringA("Czddzdzzdzd ! \n");


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

           /* std::string buffer(1024, 0);
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



void CClient::Main() 
{
    do
    {


        if (WSAAsyncSelect(clientSocket, window_, WM_SOCKET, FD_READ) != SOCKET_ERROR)
        {
            std::string buffer(1024, 0);
            int num_bytes_received = recv(clientSocket, &buffer[0], buffer.size(), 0);
            if (num_bytes_received == SOCKET_ERROR) {
            }
            else {
                std::cout << "Données reçues du serveur : " << buffer.substr(0, num_bytes_received) << std::endl;
            }

        }


        //if (GetAsyncKeyState('G') & 0x8000) {
        //    char buffedr[1024] = "CouCou serv !"; // la chaîne de caractères à envoyer
        //    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        //        std::cout << "Données envoyé : " << buffedr << " : " << std::endl;
        //    }
        //    else
        //        std::cout << "Données pas envoyé : " << std::endl;

        //}


    } while (true);

   

    // Spécifier l'adresse du serveur
    

    // Envoyer la requête HTTP

    char buffedr[1024] = "CouCou serv !"; // la chaîne de caractères à envoyer
    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        std::cout << "Données envoyé : " << buffedr << std::endl;
    }
    else
        std::cout << "Données pas envoyé : " << std::endl;


    char key;
    

    do 
    {


        if (WSAAsyncSelect(clientSocket, window_, WM_SOCKET, FD_READ) != SOCKET_ERROR)
        {
            std::string buffer(1024, 0);
            int num_bytes_received = recv(clientSocket, &buffer[0], buffer.size(), 0);
            if (num_bytes_received == SOCKET_ERROR) {
            }
            else {
                std::cout << "Données reçues du serveur : " << buffer.substr(0, num_bytes_received) << std::endl;
            }

        }

       
        //if (GetAsyncKeyState('G') & 0x8000) {
        //    char buffedr[1024] = "CouCou serv !"; // la chaîne de caractères à envoyer
        //    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        //        std::cout << "Données envoyé : " << buffedr << " : " << std::endl;
        //    }
        //    else
        //        std::cout << "Données pas envoyé : " << std::endl;

        //}


    } while (true);

}




