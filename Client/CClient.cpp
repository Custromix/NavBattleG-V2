#include "framework.h"
#include <Ws2tcpip.h>
#include <conio.h>
CClient::CClient(HWND window)
{
    window_ = window;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup a �chou� avec l'erreur : " << WSAGetLastError() << std::endl;
    }

    // Cr�er un socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Erreur de cr�ation du socket : " << WSAGetLastError() << std::endl;
    }
}

CClient::~CClient()
{
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
        closesocket(clientSocket);
        WSACleanup();
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    serverAddr.sin_port = htons(std::stoi(port));

    // Se connecter au serveur
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Impossible de se connecter au serveur : " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
    }

    char buffedr[1024] = "CouCou serv !"; // la cha�ne de caract�res � envoyer
    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        std::cout << "Donn�es envoy� : " << buffedr << std::endl;
    }
    else
        std::cout << "Donn�es pas envoy� : " << std::endl;

    return false;
}

void CClient::Main() 
{
    

   

    // Sp�cifier l'adresse du serveur
    

    // Envoyer la requ�te HTTP

    char buffedr[1024] = "CouCou serv !"; // la cha�ne de caract�res � envoyer
    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        std::cout << "Donn�es envoy� : " << buffedr << std::endl;
    }
    else
        std::cout << "Donn�es pas envoy� : " << std::endl;


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
                std::cout << "Donn�es re�ues du serveur : " << buffer.substr(0, num_bytes_received) << std::endl;
            }

        }

       
        //if (GetAsyncKeyState('G') & 0x8000) {
        //    char buffedr[1024] = "CouCou serv !"; // la cha�ne de caract�res � envoyer
        //    if (send(clientSocket, buffedr, strlen(buffedr), 0) != SOCKET_ERROR) {
        //        std::cout << "Donn�es envoy� : " << buffedr << " : " << std::endl;
        //    }
        //    else
        //        std::cout << "Donn�es pas envoy� : " << std::endl;

        //}


    } while (true);

    // Fermer le socket et lib�rer les ressources Winsock
    closesocket(clientSocket);
    WSACleanup();
}




