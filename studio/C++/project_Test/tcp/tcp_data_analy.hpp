#pragma once
#include <string>
#include "tcp_define.hpp"
#include <vector> 

using namespace TD;
class TcpDataAnaly
{
private:
    /* data */
public:
    TcpDataAnaly(/* args */);

    void add(char *d,int lenght);

    void setCallFun(RecDataFun fun);

    static MessageData getMessageData(uint8_t *app_data,const int &app_lenght);

    static MessageBody getMessageBody(uint8_t *app_data,const int &app_lenght,const int &body_lenght);

    static std::tuple<MessageData, MessageBody> getMessage(uint8_t *data,const int &msglenght);
private:
    void dealData();

    void resetData();

    void usePackData(void *use,int size);

    void dealRemainData();

    char            pack_data[MAX_LENGHT];
    int             fill_lenght=0;
    int             use_lenght=0;
    bool            is_new_data = true;
    TCP_PACKET_HEADER   head_data;
    RecDataFun      m_RecDataFun=nullptr;
};

