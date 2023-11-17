#pragma once
#include <string>
#include "tcp_define.hpp"

using namespace TD;
class TcpDataFill
{
private:
    /* data */
public:
    TcpDataFill(/* args */);

    static void packData(uint8_t *des_data,void* src_data,int size,int &lenght);

    static void fillAppDataAndCall(uint8_t *app_data, int app_dataLenght,RecDataFun fun);

    static void fillMessagAndCall(MessageData &msgData,MessageBody &body,RecDataFun fun);

    static void fillReSendData(uint8_t *data, int msglenght);

private:
    static uint8_t *fillData(uint8_t *app_data, int app_dataLenght, int &sendLenght);

    static void freeData(uint8_t *sendMsg);

    static void convertTimeToBytes(uint8_t* data);
};

