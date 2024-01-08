#pragma once
#include <string>
#include "tcp_define.hpp"
#include "singleton/singleton.h"
#include "queue.h"

using namespace TD;

class TcpSend : public Singleton<TcpSend> 
{
public:
    TcpSend(Token token);
    ~TcpSend();

    void init();

    void sendAppData(uint8_t *app_data,int lenght,bool isAck);

    void sendMessage(AppData &data);

    void setRecMessageFun(RecDataFun fun);

    void sendMsg(uint8_t *data, int msgLenght,bool isAck);

private:
    void processAppDataThread(std::string topic,int status);

    void processAppData();

    RecDataFun m_RecMessageFun = nullptr;
    PolyIC::Queue m_Queue;
    bool is_startThread = false;
};

