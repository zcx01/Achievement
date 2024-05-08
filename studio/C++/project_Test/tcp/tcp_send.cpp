#include "tcp_send.hpp"
#include "ic_log.h"
#include "tcp_data_fill.hpp"
#include "Internal_message_center.h"
#include <iostream>
#include <thread>
#include "tcp_client.hpp"


TcpSend::TcpSend(Token token) 
{
}

TcpSend::~TcpSend() 
{
}

void TcpSend::init()
{
    fds::registerSigChangeFun(std::bind(&TcpSend::processAppDataThread,
    this,std::placeholders::_1,std::placeholders::_2),TCPCONNECTSTATUS);
}

void TcpSend::processAppDataThread(std::string topic,int status)
{
    if(topic ==  TCPCONNECTSTATUS && status == TD::ConnectSuccess && !is_startThread)
    {
        std::thread(&TcpSend::processAppData,this).detach();
        is_startThread = true;
    }
}

void TcpSend::sendAppData(uint8_t *app_data, int lenght,bool isAck)
{
    TcpDataFill::fillAppDataAndCall(app_data, lenght, std::bind(&TcpSend::sendMsg, this, std::placeholders::_1, std::placeholders::_2,isAck));
}

void TcpSend::sendMessage(AppData &data)
{
    m_Queue.put(PolyIC::DataMsg<AppData>(0, data));
}

void TcpSend::processAppData()
{
    pthread_setname_np(pthread_self(), "TcpSend");
    IC_LOG_INFO("processAppData");
    while (1)
    {
        auto m = m_Queue.get();
        auto &dm = dynamic_cast<PolyIC::DataMsg<AppData> &>(*m);
        AppData appData = dm.getPayload();
        try
        {
            TcpDataFill::fillMessagAndCall(appData.data,appData.body, std::bind(&TcpSend::sendAppData, this, std::placeholders::_1, std::placeholders::_2, appData.data.ackFlag));
        }
        catch (...)
        {
            IC_LOG_ERROR("TcpSend is error");
        }
    }
}

void TcpSend::setRecMessageFun(RecDataFun fun)
{
    m_RecMessageFun = fun;
}

void TcpSend::sendMsg(uint8_t *data, int msgLenght,bool isAck)
{
    if (m_RecMessageFun && isAck)
    {
        m_RecMessageFun(data, msgLenght);
    }
    TcpClient::instance().sendMsg(data,msgLenght);
}

