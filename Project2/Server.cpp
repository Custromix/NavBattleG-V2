#include "Utils.h"

Server::Server(int port, HWND window)
{
    window_ = window;
    statusServ = ServerStatus::WAITING;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup a échoué avec l'erreur : " + WSAGetLastError());
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        throw std::runtime_error("Erreur de création du socket : " + WSAGetLastError());
        WSACleanup();
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(27523);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la liaison du socket : " + WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }


    InitCommand();
}

Server::~Server()
{
}

void Server::InitCommand() 
{
    command["server:start"] = 1;
    command["server:stop"] = 0;
}


void Server::StopServer()
{
    closesocket(serverSocket);
    WSACleanup();
}

bool Server::Waiting(int clientMax)
{
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    int numberOfClient = 0;

    while(numberOfClient < clientMax)
    {
        std::cout << "En attente" << std::endl;

        if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
            std::cout << "Client connecté" << std::endl;
            SClient* player = new SClient(clientSocket, clientAddr, window_);
            if (Join(player)) 
                numberOfClient++;
            std::cout << "Il manque " << clientMax - numberOfClient << " joueurs !" << std::endl;

        }
    }
    
    return true;
}

void Server::Start() 
{
    do 
    {
        switch (statusServ)
        {
        case WAITING:
            if (Waiting(2))
                statusServ = PLAY;
            break;

        case PLAY:
            if (Play())
                statusServ = STOP;
            break;

        default:
            //std::cout << "Default" << std::endl;
            break;
        }

    } while (statusServ != STOP);
    

    
}

bool Server::Play()
{
    bool endGame = false;
    do {

        /*** EXAMPLE MODIFIER TOUT CE QU'IL Y A DANS LA BOUCLE DO POUR LE JEU ***/

        std::cout << "Envoie des données ! " << std::endl;

        SendToClient(clients[0], "Ta grands mère la prostitué");
        SendToClient(clients[1], "Réveilles toi PD");

        ReceiveFromClient(clients[0]);
        ReceiveFromClient(clients[1]);


        /*** JUSQU'A LÀ ***/


        endGame = true;

    } while (endGame != true);

    return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_SOCKET:
    {
        if (WSAGETSELECTERROR(lParam)) {
            // Il y a eu une erreur
        }
        else {
            switch (WSAGETSELECTEVENT(lParam)) {
            case FD_ACCEPT:
            {

                break;
            }
            case FD_READ:
            {
                char buffer[1024];
                int bytesReceived = 0;//recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived == SOCKET_ERROR) {
                    // Il y a eu une erreur
                }
                else {
                    std::cout << "Données reçues : " << buffer << std::endl;
                    // Traitez les données reçues ici
                }
                break;
            }
            case FD_CLOSE:
            {
                // Le socket a été fermé
                break;
            }

            default:
                break;
            }
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);

    }
    return 0;
}

bool Server::Join(SClient* joiningClient)
{
	if (!IsExist(joiningClient)->GetStatus())
	{
		clients.push_back(joiningClient);
        return true;
    }
    else
        return false;
    
}

void Server::Leave(SClient* leavingClient)
{
	if (IsExist(leavingClient)->GetStatus())
	{

	}
}

CResult<int>* Server::IsExist(SClient* client)
{
    CResult<int>* result = new CResult<int>(false);

    if (client == nullptr) {
        throw std::invalid_argument("Client pointer is null.");
    }

    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] == client) {
            result->SetSatue(true);
            result->SetValue(i);
            return result;
        }
    }

    return result;
}

bool Server::DeleteUsers(SClient* client)
{
    if (IsExist(client)->GetStatus()) 
    {
        auto it = std::remove(clients.begin(), clients.end(), client);
        clients.erase(it, clients.end());
        return true;
    }
    else
        return false;
}

bool Server::Listen()
{
    currentCommand = "";

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        throw std::runtime_error("Erreur lors de la mise en mode écoute du socket : " + WSAGetLastError());
        StopServer();
    }
    else
        std::cout << "Le serveur est à l'écoute sur le port : " << serverAddr.sin_port << std::endl;
    return true;

}

void Server::SendToClient(SClient* receiver, std::string message)
{

    if (send(*receiver->GetSocket(), message.c_str(), message.length(), 0)) {
        std::cout << "Données envoyées : " << message << std::endl;
        //satusServ = STOP;
    }
    else
        std::cout << "Données pas envoyé : " << std::endl;

    /*
    if (WSAAsyncSelect(*receiver->GetSocket(), window_, WM_SOCKET, FD_READ) != SOCKET_ERROR)
    {
        std::string buffer(1024, 0);
        int num_bytes_received = recv(*receiver->GetSocket(), &buffer[0], buffer.size(), 0);

        if (num_bytes_received != SOCKET_ERROR)
        {
            std::cout << "Données reçues du serveur : " << buffer.substr(0, num_bytes_received) << std::endl;

            

        }
    }*/
}

std::string Server::ReceiveFromClient(SClient* emitter)
{
  /*  if (WSAAsyncSelect(*emitter->GetSocket(), window_, WM_SOCKET, FD_READ ) != SOCKET_ERROR)
    {
        std::string buffer(1024, 0);
        int num_bytes_received = recv(*emitter->GetSocket(), &buffer[0], buffer.size(), 0);

        if (num_bytes_received != SOCKET_ERROR)
        {
            std::cout << "Données reçues du serveur : " << buffer.substr(0, num_bytes_received) << std::endl;
            return buffer;
        }

        return "NULL";
    }

    return "";*/

    return "";
}

bool Server::Clear()
{

    return false;
}


