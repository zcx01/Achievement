#include "tcp_data_analy.hpp"
#include <iostream>
#include <string.h>
#include "ic_log.h"


TcpDataAnaly::TcpDataAnaly(/* args */) 
{
    resetData();
}

void TcpDataAnaly::add(char *d, int lenght)
{
    memcpy(pack_data + fill_lenght, d, lenght);
    fill_lenght += lenght;
    dealData();
}

void TcpDataAnaly::setCallFun(RecDataFun fun)
{
    m_RecDataFun = fun;
}

MessageData TcpDataAnaly::getMessageData(uint8_t *app_data,const int &app_lenght)
{
    MessageData messageData;
    int messageDataLenght =  sizeof(MessageData);
    memset(&messageData, 0,messageDataLenght);
    if (app_lenght >= messageDataLenght)
        memcpy(&messageData, app_data, messageDataLenght);
    return messageData;
}

MessageBody TcpDataAnaly::getMessageBody(uint8_t *app_data,const int &app_lenght,const int &body_lenght)
{
    MessageBody messageBody;
    int useLenght = sizeof(MessageData);
    if (app_lenght - useLenght >= messageBody.getRSMlenght())
        memcpy(&messageBody, app_data + useLenght, messageBody.getRSMlenght());
    if (app_lenght - useLenght >= body_lenght)
        messageBody.TLVs = std::vector<uint8_t>(app_data + useLenght + messageBody.getRSMlenght() , app_data + useLenght + body_lenght);
    return messageBody;
}

std::tuple<MessageData, MessageBody> TcpDataAnaly::getMessage(uint8_t *data, const int &msglenght)
{
    int app_lenght = msglenght-sizeof(TCP_PACKET_HEADER) - CRCLENGHT; // 2是crc
    MessageData messageData = getMessageData(data+sizeof(TCP_PACKET_HEADER),app_lenght);
    MessageBody messageBody = TcpDataAnaly::getMessageBody(data+sizeof(TCP_PACKET_HEADER), app_lenght, 
    convertBigEndianToInt(messageData.messageBodyLenght, sizeof(messageData.messageBodyLenght)));
    return std::make_tuple(messageData, messageBody);
}

void TcpDataAnaly::dealData()
{
    if (is_new_data)
    {
        //解析头
        auto head_lenght = sizeof(head_data);
        while (fill_lenght - use_lenght > head_lenght)
        {
            uint8_t headflg  = pack_data[use_lenght];
             //如果不是0x5a开头的就丢弃，
            if(headflg != HEADERFLAG)
            {
                ++use_lenght;
            }
            else
            {
                usePackData(&head_data,head_lenght);
                is_new_data = false;
                dealData();
                return;
            }
        }
        IC_LOG_ERROR("fill_lenght: %d,use_lenght:%d,head_lenght:%d",fill_lenght,use_lenght,head_lenght);
        return;
    }
    else
    {
        //获取app-data数据和crc校验 crc是2个字节
        int crc_lenght = 2;
        int app_data_lenght = convertLittleEndianToInt(head_data.length);
        int data_total_length = (app_data_lenght + crc_lenght);
        if (fill_lenght - use_lenght < data_total_length)
        {
           
            IC_LOG_ERROR("fill_lenght：%d,use_lenght:%d,data_total_length:%d",fill_lenght,use_lenght,data_total_length);
            return;
        }
        uint8_t app_data[app_data_lenght];
        usePackData(app_data, app_data_lenght);

        uint8_t crc_data[CRCLENGHT];
        usePackData(crc_data,sizeof(crc_data));
        //校验
        printHex("crc_data",crc_data,sizeof(crc_data));
        if(!checkCrc(crc_data,app_data,app_data_lenght))
        {
            IC_LOG_ERROR("check crc fail!");
            return;
        }
        
        //回调处理
        printHex("deal Data:",app_data,app_data_lenght);

        if (m_RecDataFun != nullptr)
        {
            m_RecDataFun(app_data, app_data_lenght);
        }
        
        //处理下一包的数据
        if (fill_lenght > use_lenght)
        {
            IC_LOG_INFO("fill_lenght：%d,use_lenght:%d",fill_lenght,use_lenght);
            dealRemainData();
        }
        else
        {
            resetData();
        }
    }   
}

void TcpDataAnaly::resetData()
{
    memset(pack_data,0,sizeof(pack_data));
    memset(&head_data,0,sizeof(head_data));
    is_new_data = true;
    fill_lenght = 0;
    use_lenght = 0;
}


void TcpDataAnaly::usePackData(void *use,int size)
{
    memcpy(use, pack_data + use_lenght,size);
    use_lenght += size;
}


void TcpDataAnaly::dealRemainData()
{
    int remain_lenght = fill_lenght - use_lenght; // 还没有使用的长度
    uint8_t remain_data[remain_lenght];
    usePackData(remain_data, remain_lenght);
    resetData();
    memcpy(pack_data, remain_data, remain_lenght);
    fill_lenght += remain_lenght;
    dealData();
}

