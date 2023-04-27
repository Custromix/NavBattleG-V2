#pragma once

class Server
{

public:
	Server(int port, HWND window);
	~Server();

	void InitCommand();

	void StopServer();

	bool Connect(WPARAM wParam, HWND window);

	bool Waiting(int clientMax);

	void Start();

	bool Play();

	bool Join(SClient* joiningClient);

	bool DeleteUsers(SClient* client);
	void Leave(SClient* leavingClient);

	CResult<int>* IsExist(SClient* client);

	bool Listen();
	void ListenCommand(int command);

	void SendToClient(SClient* receiver, std::string message);

	std::string ReceiveFromClient(SClient* receiver);

	bool Clear();

	static LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


	std::vector<SClient*> GetClients() { return clients; }

	enum ServerStatus
	{
		WAITING,
		PLAY,
		STOP
	};


	SOCKET* GetServerSocket() { return &serverSocket; }
	HWND* GetWindow() { return &window_; }

private:
	std::vector<SClient*> clients;
	WSADATA wsaData;
	SOCKET serverSocket;
	sockaddr_in serverAddr;

	std::map<std::string, int> command;
	std::string currentCommand;

	HWND window_;

	ServerStatus statusServ;




};


