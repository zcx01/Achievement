#include "tcp_send.hpp"
#include "ic_log.h"
#include "tcp_data_fill.hpp"
#include <iostream>


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAXLINE 4096

TcpSend::TcpSend(Token token) 
{
    connectPort(TCP_IP,TCP_PORT);
}

TcpSend::~TcpSend() 
{
    if(sockfd != 0) close(sockfd);
}

void TcpSend::sendAppData(uint8_t *app_data, int lenght)
{
    TcpDataFill::fillAppDataAndCall(app_data, lenght, std::bind(&TcpSend::sendMsg, this, std::placeholders::_1, std::placeholders::_2,true));
}

void TcpSend::sendMessage(MessageData msgData,MessageBody body)
{
    TcpDataFill::fillMessagAndCall(msgData, body, std::bind(&TcpSend::sendAppData, this, std::placeholders::_1, std::placeholders::_2));
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
    TD::printHex("send msg:", data, msgLenght);
    if (send(sockfd, data, msgLenght, 0) < 0)
    {
        IC_LOG_INFO("send msg error: %s(errno: %d)", strerror(errno), errno);
    }
}

int TcpSend::connectPort(std::string ip, int port) 
{
    IC_LOG_INFO("%s:%u",ip.c_str(),port);
    struct sockaddr_in  servaddr;

    if( ip.empty()){
        IC_LOG_INFO("usage: ./client <ipaddress>");
        return -1;
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        IC_LOG_INFO("create socket error: %s(errno: %d)", strerror(errno),errno);
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if( inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0){
        IC_LOG_INFO("inet_pton error for %s",ip.c_str());
        return -1;
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        IC_LOG_INFO("connect error: %s(errno: %d)",strerror(errno),errno);
        return -1;
    }

    return 0;
}
