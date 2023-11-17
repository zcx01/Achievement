#pragma once
#include <string>
#include "tcp_define.hpp"
#include "tcp_data_analy.hpp"
#include "singleton/singleton.h"

class TcpService : public Singleton<TcpService>
{
public:
    TcpService(Token token);

    void addCallFun(RecDataFun fun);
private:
    void onMessageArrival(uint8_t *msg, int lenght);

    int listenPort(int port=TCP_PORT);

    TcpDataAnaly data_analy;

    std::vector<RecDataFun> m_funs;
};

class TcpReceive
{
public:
    TcpReceive(/* args */);
    virtual ~TcpReceive();

    virtual bool onAppDatarrival(uint8_t *msg, int lenght){ return true;}
    virtual bool onMessageDataArrival(MessageData msgData){ return true;}
    virtual bool onMessageBodyArrival(MessageBody msgBody){ return true;}
    virtual bool onMessageDataAndBodyArrival(MessageData msgData,MessageBody msgBody){ return true;}
private:
    void dealAppData(uint8_t *app_data, int app_lenght);
    /* data */
};

