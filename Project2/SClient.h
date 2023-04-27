
class SClient
{

private:
    SOCKET clientSocket_;
    sockaddr_in clientAddr_;
    int clientAddrSize_;

public:

    SClient();
    SClient(SOCKET clientSocket, sockaddr_in clientAddr);

    ~SClient();

    SOCKET* GetSocket()                                     { return &clientSocket_; }
    sockaddr_in* GetSockAddr()                              { return &clientAddr_; }
    int* GetSockAddrSize()                                  { return &clientAddrSize_; }

    void SetSocket(SOCKET sock)                             { clientSocket_ = sock; }
    void SetSockAddr(sockaddr_in sockAddr);

};

