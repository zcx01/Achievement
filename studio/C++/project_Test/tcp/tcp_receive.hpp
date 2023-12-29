#pragma once
#include <string>
#include "tcp_define.hpp"
#include "singleton/singleton.h"

using namespace TD;
class TcpBaseReceive
{
private:
    /* data */
public:
    TcpBaseReceive(/* args */);
    ~TcpBaseReceive();

protected:
    virtual bool onAppDataArrival(uint8_t *app_data, int app_lenght){ return true;}
    virtual void dealAppData(uint8_t *app_data, int app_lenght){};
    virtual uint32_t getType() = 0;

private:
    void receiveAppData(uint8_t *app_data, int app_lenght);
};

class TcpTspReceive : public TcpBaseReceive
{
public:
    using TcpBaseReceive::TcpBaseReceive;
    virtual bool onMessageDataArrival(MessageData msgData){ return true;}
    virtual bool onMessageBodyArrival(MessageBody msgBody){ return true;}
    virtual bool onMessageDataAndBodyArrival(MessageData msgData,MessageBody msgBody){ return true;}
private:
    void dealAppData(uint8_t *app_data, int app_lenght);
    uint32_t getType();
};

