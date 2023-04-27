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

    WSAAsyncSelect(serverSocket, window, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

    SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);

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

bool Server::Connect(WPARAM wParam, HWND window)
{
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    int numberOfClient = 0;

    if ((clientSocket = accept(wParam, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
        SClient* player = new SClient(clientSocket, clientAddr, window);
        if (Join(player)) 
        {
            numberOfClient++;
            OutputDebugStringA("Client connecté !");
           
        }

    }
    return true;
}

void Server::Start() 
{
    //do 
    //{
    //    switch (statusServ)
    //    {
    //    case WAITING:
    //        if (Waiting(2))
    //            statusServ = PLAY;
    //        break;

    //    case PLAY:
    //        if (Play())
    //            statusServ = STOP;
    //        break;

    //    default:
    //        //std::cout << "Default" << std::endl;
    //        break;
    //    }

    //} while (statusServ != STOP);
    

    
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

LRESULT CALLBACK Server::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SOCKET Accept;

    switch(uMsg)

    {

        case WM_PAINT:

            break;

        case WM_SOCKET:

            if (WSAGETSELECTERROR(lParam))
            {
                closesocket( (SOCKET) wParam);
                break;
            }

            // Determine what event occurred on the socket

            switch(WSAGETSELECTEVENT(lParam))
            {
                case FD_ACCEPT:
                {
                    Server* pServer = (Server*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

                    OutputDebugStringA("GrosZgeg");

                    if (pServer->Connect(wParam, hwnd)) {

                    }
                    // Accept an incoming connection
                    Accept = accept(wParam, NULL, NULL);

                    // Prepare accepted socket for read, write, and close notification

                    //WSAAsyncSelect(Accept, hDlg, WM_SOCKET, FD_READ │ FD_WRITE │ FD_CLOSE);

                    break;
                }
                case FD_READ:
                {
                    // Receive data from the socket in wParam

                    break;
                }
                case FD_WRITE:
                {
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

    return TRUE;
}

LRESULT CALLBACK WndPdroc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    std::cout << "Enter WindProc : " << std::endl;

    switch (uMsg)
    {
    case WM_CREATE:
    {
        return 0;
    }
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
        return DefWindowProc(hwnd, uMsg, wParam, lParam);

    }
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
        std::cout << "Le serveur estzdzdzd : " << std::endl;
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


