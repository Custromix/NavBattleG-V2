#include "Sframework.h"

Server::Server(int port, HWND window)
{
    window_ = window;
    statusServ = ServerStatus::WAITING;
    pGame = new GameManager();
    pQMM = new QueueMessageManager();

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

bool Server::Connect(WPARAM wParam, HWND window)
{
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    int numberOfClient = 0;

    if ((clientSocket = accept(wParam, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
        SClient* player = new SClient(clientSocket, clientAddr, window);
        if (Join(player)) 
            numberOfClient++;           

    }
    return true;
}

std::vector<std::string>* Server::Parser(std::string ProtocolMessage)
{
    std::istringstream ss(ProtocolMessage);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ':'))
    {
        tokens.push_back(token);
    }

    return &tokens;

}

bool Server::ProtocolExecuter(std::vector<std::string>* tokens)
{
    pQMM->EnqueueMessage("MISS", clients[0]);

    return false;
}

void Server::SendToClient(SClient* receiver, std::string message)
{
    if (send(*receiver->GetSocket(), message.c_str(), message.length(), 0)) {
    }
    
}


LRESULT CALLBACK Server::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            Server* pServer = (Server*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if (WSAGETSELECTERROR(lParam))
            {
                closesocket((SOCKET)wParam);
                break;
            }

            // Determine what event occurred on the socket

            switch (WSAGETSELECTEVENT(lParam))
            {
                case FD_ACCEPT:
                {                            

                    if (pServer->GetClients()->size() < pServer->GetSlot())
                    {
                        if (pServer->Connect(wParam, hwnd)) {
                            OutputDebugStringA("Client connecté ! \n");
                        }
                    }

                    break;
                }
                case FD_READ:
                {

                    std::string buffer(1024, 0);
                    int num_bytes_received = recv(wParam, &buffer[0], buffer.size(), 0);

                    if (num_bytes_received != SOCKET_ERROR)
                    {
                        OutputDebugStringA("\n");
                        OutputDebugStringA(buffer.c_str());
                        OutputDebugStringA("\n");
                        pServer->ProtocolExecuter(pServer->Parser(buffer));
                    }

                    // Receive data from the socket in wParam

                    break;
                }
                case FD_WRITE:
                {
                    if (!pServer->pQMM->IsEmpty()) 
                    {
                        OutputDebugStringA("SEND MESSAGE \n");
                        SMessage message = pServer->pQMM->DequeueMessage();
                        pServer->SendToClient(message.GetClient(), message.GetSMessage());
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

LRESULT CALLBACK WndPdroc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

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



void Server::Leave(SClient* leavingClient)
{
	if (IsExist(leavingClient)->GetStatus())
	{

	}
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






bool Server::Clear()
{

    return false;
}


