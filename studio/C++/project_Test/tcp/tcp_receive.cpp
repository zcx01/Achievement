#include "tcp_receive.hpp"
#include "ic_log.h"
#include <iostream>
#include "Internal_message_center.h"
#include "tcp_client.hpp"


TcpBaseReceive::TcpBaseReceive(/* args */)
{
    TcpClient::instance().addCallFun([=](uint8_t *data, int lenght)
                                     { receiveAppData(data, lenght); });
}

TcpBaseReceive::~TcpBaseReceive()
{
}

void TcpBaseReceive::receiveAppData(uint8_t *app_data, int app_lenght)
{
    if(app_lenght < 0)
    {
        IC_LOG_INFO("Receive data lenght is error:%d", app_lenght);
        return;
    }

    if(!onAppDataArrival(app_data,app_lenght))
    {
        return;
    }
    uint8_t type = app_data[0];
    if(getType() == type)
    {
        dealAppData(app_data,app_lenght);
    }
}


void TcpTspReceive::dealAppData(uint8_t *app_data, int app_lenght)
{
    MessageData msgData =  TcpDataAnaly::getMessageData(app_data,app_lenght);
    if (msgData.up_down == 0x02)
    {
        if (!onMessageDataArrival(msgData))
        {
            return;
        }
        MessageBody msgBody = TcpDataAnaly::getMessageBody(app_data, app_lenght, convertBigEndianToInt(msgData.messageBodyLenght, sizeof(msgData.messageBodyLenght)));
        if (!onMessageBodyArrival(msgBody))
        {
            return;
        }
        if (!onMessageDataAndBodyArrival(msgData, msgBody))
        {
            return;
        }
    }
    else
    {
        IC_LOG_INFO("Receive data not is down,is:%d", (int)msgData.up_down);
        return;
    }
}

uint32_t TcpTspReceive::getType()
{
    return 0x0;
}
