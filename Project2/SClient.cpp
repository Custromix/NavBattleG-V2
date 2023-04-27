#include "Utils.h"

SClient::SClient()
{
}

SClient::SClient(SOCKET clientSocket, sockaddr_in clientAddr)
{
	clientSocket_ = clientSocket;
	clientAddr_ = clientAddr;
	clientAddrSize_ = sizeof(clientAddr_);
}

SClient::~SClient()
{
}

void SClient::SetSockAddr(sockaddr_in sockAddr)
{
	clientAddr_ = sockAddr;
	clientAddrSize_ = sizeof(clientAddr_);
}
