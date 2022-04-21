#pragma once
#include <string>
#include <functional>

using RecDataFun = std::function<void (char*,int)>;

class TcpServiceTest
{
private:
    /* data */
public:
    TcpServiceTest(/* args */);

    int listenPort(int port);

    void SetCallFun(RecDataFun f){m_call =f;}
private:
    RecDataFun m_call=nullptr;
};

