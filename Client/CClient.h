#pragma once
class CClient
{
public:
	CClient(HWND window);
	~CClient();

	bool Connect(const char ip[], const char port[]);

	void SendToServer(std::string message);

	void sendMes();

	void Main();

	void ProtocolExecuter(std::string);

	static LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

	QueueMessageManager* pQMM;

private:
	HWND window_;

	WSADATA wsaData;
	SOCKET clientSocket;



};