#include "Sframework.h"

SClient::SClient()
{
}

SClient::SClient(SOCKET clientSocket, sockaddr_in clientAddr, HWND window)
{
	clientSocket_ = clientSocket;
	clientAddr_ = clientAddr;
	clientAddrSize_ = sizeof(clientAddr_);

	WSAAsyncSelect(clientSocket, window, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
}

SClient::~SClient()
{
}

void SClient::SetSockAddr(sockaddr_in sockAddr)
{
	clientAddr_ = sockAddr;
	clientAddrSize_ = sizeof(clientAddr_);
}
