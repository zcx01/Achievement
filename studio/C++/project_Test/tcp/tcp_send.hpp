#pragma once
#include <string>
#include "tcp_define.hpp"
#include "singleton/singleton.h"

using namespace TD;

class TcpSend : public Singleton<TcpSend>
{
public:
    TcpSend(Token token);
    ~TcpSend();

    void sendAppData(uint8_t *app_data,int lenght);

    void sendMessage(MessageData msgData,MessageBody body);

    void setRecMessageFun(RecDataFun fun);

    void sendMsg(uint8_t *data, int msgLenght,bool isAck);
private:
    int connectPort(std::string ip,int port);

    int sockfd = 0;

    RecDataFun m_RecMessageFun = nullptr;
};

