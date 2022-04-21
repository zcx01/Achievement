#pragma once
#include <string>

class TcpClientTest
{
private:
    /* data */
public:
    TcpClientTest(/* args */);
    ~TcpClientTest();

    int connectPort(std::string ip,int port);

private:
    int sockfd = 0;
};

