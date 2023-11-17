#include "tcp_data_fill.hpp"
#include <iostream>
#include "ic_log.h"
#include <cstring>
#include <ctime>

using namespace TD;
TcpDataFill::TcpDataFill(/* args */) 
{

}

void TcpDataFill::fillAppDataAndCall(uint8_t *app_data, int app_dataLenght, RecDataFun fun)
{
    int sendLenght;
    uint8_t *sendMsg = fillData(app_data,app_dataLenght,sendLenght);
    if(fun)
    {
        fun(sendMsg,sendLenght);
    }
    freeData(sendMsg);
}

void TcpDataFill::convertTimeToBytes(uint8_t* data)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);

    uint16_t year = timeInfo->tm_year + 1900;
    data[0] = (year >> 6) & 0xFF;
    data[1] = ((year & 0x3F) << 2) | ((timeInfo->tm_mon + 1) >> 2);

    data[2] = (((timeInfo->tm_mon + 1) & 0x03) << 6) | ((timeInfo->tm_mday) << 1) | (timeInfo->tm_hour >> 4);

    data[3] = ((timeInfo->tm_hour & 0x0F) << 4) | (timeInfo->tm_min >> 2);

    data[4] = ((timeInfo->tm_min & 0x03) << 6) | (timeInfo->tm_sec);
}

void TcpDataFill::fillMessagAndCall(MessageData &msgData,MessageBody &body, RecDataFun fun)
{
    int app_lenght = sizeof(MessageData) + body.getRSMlenght() + body.TLVs.size();
    int useLenght = 0;

    msgData.up_down = 0x01;
    msgData.statusCode = 0x00;
    msgData.ackFlag = 0x01;
    convertTimeToBytes(msgData.requestId);
    static uint8_t serialNumber = 0;
    msgData.requestId[5] = 0x01 | serialNumber << 2;
    serialNumber >= 62 ? serialNumber = 0 : serialNumber += 2;
    convertIntToBigEndianArray(body.TLVs.size() + body.getRSMlenght(), msgData.messageBodyLenght, sizeof(msgData.messageBodyLenght));

    uint8_t app_data[app_lenght];
    memcpy(app_data + useLenght, &msgData, sizeof(MessageData));
    useLenght += sizeof(MessageData);

    memcpy(app_data + useLenght, &body, body.getRSMlenght());
    useLenght += body.getRSMlenght();
    memcpy(app_data + useLenght, body.TLVs.data(), body.TLVs.size());
    useLenght += body.TLVs.size();
    fun(app_data,app_lenght);
}

void TcpDataFill::fillReSendData(uint8_t *data, int msglenght)
{
    int startRand = sizeof(TCP_PACKET_HEADER) + sizeof(MessageData);
    MessageBody body;
    memcpy(data + startRand, body.Random, sizeof(startRand));

    uint8_t crc[CRCLENGHT] = {};
    int app_lenght = msglenght - sizeof(TCP_PACKET_HEADER) - CRCLENGHT; // 2是crc
    crcCalculate(crc, data + sizeof(TCP_PACKET_HEADER), app_lenght);
    memcpy(data + msglenght - CRCLENGHT, crc, CRCLENGHT);
}

uint8_t* TcpDataFill::fillData(uint8_t *app_data, int app_dataLenght, int &sendLenght)
{
    static uint16_t counter = 0;
    sendLenght = 0;
    uint8_t crc[CRCLENGHT]={};
    crcCalculate(crc, (uint8_t *)app_data, app_dataLenght);

    TCP_PACKET_HEADER head;
    head.flag = 0x5a;
    convertIntToLittleEndian(app_dataLenght, head.length);
    convertIntToLittleEndian(counter, head.counter);
    counter >= 65535 ? counter = 0 : ++counter;

    sendLenght = sizeof(head)+app_dataLenght+sizeof(crc);
    auto sendMsg = new uint8_t[sendLenght];
    int lenght = 0;
    packData(sendMsg,&head,sizeof(head),lenght);
    packData(sendMsg,app_data,app_dataLenght,lenght);
    packData(sendMsg,crc,sizeof(crc),lenght);

    
    return sendMsg;
}

void TcpDataFill::packData(uint8_t *des_data, void *src_data, int size, int &lenght)
{
    memcpy(des_data + lenght, src_data, size);
    lenght += size;
}

void TcpDataFill::freeData(uint8_t *sendMsg)
{
    if(sendMsg != nullptr)
        delete[] sendMsg;
}
