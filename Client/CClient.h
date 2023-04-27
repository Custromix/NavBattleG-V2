#pragma once
class CClient
{
public:
	CClient(HWND window);
	~CClient();

	bool Connect(const char ip[], const char port[]);

	void Main();

private :
	HWND window_;

	WSADATA wsaData;
	SOCKET clientSocket;

};

