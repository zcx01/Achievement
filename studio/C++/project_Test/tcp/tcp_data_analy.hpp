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

    static A35SendReply getA35SendReply(uint8_t *app_data,const int &app_lenght);

    static uint64_t getMessageId(uint8_t *requestId,uint32_t requestIdLenght,uint8_t sid,uint8_t mid);

    static std::vector<TLVConent> getTLV(const std::vector<uint8_t> &TLVs,uint8_t fixedlenghtSize, std::vector<uint8_t> lenghtSizes = {});

    static void setTLV(const std::vector<TLVConent> &TLVContents,std::vector<uint8_t> &TLVs);
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
    int             data_crc_start=0;
    int             data_crc_end=0;
};

