#include "tcp_data_analy_test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "tcp_data_analy.hpp"
#include "tcp_data_fill.hpp"
#include "tcp_send.hpp"
#include "tcp_receive.hpp"
#include <string.h>
#include <thread>
#include <sstream>
#include "tcp_cache_message.hpp"

class TcpReceiveTest : public TcpReceive
{
private:
    /* data */
public:
    virtual bool onMessageBodyArrival(MessageBody body)
    {
        printHex("sid",&body.sid,sizeof(body.sid));
        printHex("mid",&body.mid,sizeof(body.mid));
        std::vector<TLVConent> contents = body.getTLV(1);
        for (auto content : contents)
        {
            IC_LOG_INFO(content.type);
            printVectorHex("content",content.values);
        }
        return true;
    }
};

class TcpReceiveTest2 : public TcpReceive
{
private:
    /* data */
public:
};

std::vector<uint8_t> convertHexStringToArray(const std::string& hexString,uint8_t *app_data) {
    std::vector<uint8_t> result;

    std::istringstream iss(hexString);
    std::string byteString;
    int index = 0;
    while (iss >> byteString) {
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        app_data[index] = byte;
        index++;
    }
    return result;
}


TcpDataAnalyTestTest::TcpDataAnalyTestTest(/* args */) 
{
    TcpReceiveTest test;
    TcpCacheMessage cacheMessage;

    uint8_t app_data[12]={};
    std::string userInput;
    MessageData msgData;
    MessageBody msgBody;
    msgBody.sid = 0x12;
    msgBody.mid = 0x18;

    std::vector<TLVConent> contents;
    TLVConent content;
    content.type = 4004;
    content.values.push_back(0x15);
    content.values.push_back(0x08);
    content.values.push_back(0x09);
    contents.push_back(content);

    content.type = 4005;
    content.values.clear();
    content.values.push_back(0x01);
    content.values.push_back(0x02);
    content.values.push_back(0x03);
    contents.push_back(content);

    msgBody.setTLV(contents);

    TcpSend::instance().sendMessage(msgData,msgBody);

    std::cout << "请输入内容（输入'exit'退出）：\n";
    while (1)
    {
       std::getline(std::cin, userInput);
       if (userInput == "exit") {
            break;
        }
       convertHexStringToArray(userInput, app_data);
    //    TcpSend::instance().sendAppData(app_data,sizeof(app_data));
    }
}


CUSTOMEGISTER(TcpDataAnalyTest,TcpDataAnalyTestTest)