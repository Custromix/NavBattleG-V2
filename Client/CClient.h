#pragma once
class CClient
{
public:
	CClient(HWND window);
	~CClient();

	void Stop();

	bool Connect(const char ip[], const char port[]);

	void SendToServer(std::string message);

	static LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

	void Main();

private :
	HWND window_;

	WSADATA wsaData;
	SOCKET clientSocket;

	SOCKADDR_IN serverAddr;

	QueueMessageManager* pQMM;
};

