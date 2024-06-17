#include "tcp_client.hpp"
#include "Internal_message_center.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
#define MAXLINE 4096

TcpClient::TcpClient(Token token) 
{
    
}

TcpClient::~TcpClient() 
{
    closeConnect();
}

void TcpClient::init(std::string ip ,int port)
{
    m_ip = ip;
    m_port = port;
    fds::callTopicChanged(TCPCONNECTSTATUS,TD::NoConnect);
    data_analy.setCallFun([=](uint8_t *data, int lenght)
                          { onMessageArrival(data, lenght); });
    std::thread(&TcpClient::receiveMsg, this).detach();
}

void TcpClient::closeConnect()
{
    if (sockfd != 0)
    {
        close(sockfd);
        sockfd = 0;
        setConnectStatus(TD::DisConnect);
    }
}

void TcpClient::connectSocket(std::string ip, int port)
{
    setConnectStatus(TD::Connecting);
    int isSuccess = false;
    while (1)
    {
        if(isSuccess)
        {
            int error = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, NULL, NULL);
            if(error !=0)
            {
                if(sockfd !=0)
                {
                    closeConnect();
                }
                isSuccess = false;
                setConnectStatus(TD::DisConnect);
            }
        }
        else if(connectPort(ip,port) ==0)
        {
            isSuccess = true;
            setConnectStatus(TD::ConnectSuccess);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void TcpClient::setConnectStatus(TcpConnectStatus status)
{
    fds::callTopicChanged(TCPCONNECTSTATUS, (int)status);
}

void TcpClient::setSendStatus(const TcpSendStatus &status)
{
    fds::callTopicChanged(TCPSENDSTATUS,(int)status);
}

int TcpClient::connectPort(std::string ip, int port) 
{
    IC_LOG_INFO("%s:%u",ip.c_str(),port);
    if( ip.empty()){
        IC_LOG_INFO("usage: ./client <ipaddress>");
        return -1;
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        IC_LOG_INFO("create socket error: %s(errno: %d)", strerror(errno),errno);
        return -1;
    }

    // 设置端口复用。
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    struct sockaddr_in  addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0)
    {
        IC_LOG_INFO("inet_pton error for %s",ip.c_str());
        return -1;
    }
    // struct sockaddr_in addr;
    // addr.sin_family = AF_INET;
    // addr.sin_port = htons(port);
    // addr.sin_addr.s_addr = inet_addr(ip.c_str());
    // bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        IC_LOG_INFO("connect error: %s(errno: %d)",strerror(errno),errno);
        return -1;
    }

    return 0;
}



void TcpClient::onMessageArrival(uint8_t *msg, int lenght)
{
    for(auto fun : m_funs)
    {
        fun(msg,lenght);
    }
}

void TcpClient::addCallFun(RecDataFun fun)
{
    m_funs.push_back(fun);
}

void TcpClient::sendMsg(uint8_t *data, int msgLenght)
{
    std::unique_lock<std::mutex> lk(m_mutex);
    if(sockfd == 0)
    {
        IC_LOG_INFO("sockfd error: %d", sockfd);
        return;
    }
    //TD::printHex("send msg:", data, msgLenght);
    setSendStatus(TD::Sending);
    if (send(sockfd, data, msgLenght, 0) < 0)
    {
        setSendStatus(TD::SendFail);
        IC_LOG_INFO("send msg error: %s(errno: %d)", strerror(errno), errno);   
    }
    setSendStatus(TD::SendFinish);
}

int TcpClient::receiveMsg() 
{
    char buff[MAX_LENGHT];
    int n = 0;

    while(1)
    {
        if(sockfd != 0)
        {
            n = recv(sockfd, buff, MAX_LENGHT, 0);
        }
        if(n <= 0)
        {
            std::unique_lock<std::mutex> lk(m_mutex);
            IC_LOG_INFO("TcpClient accept socket error: %s(errno: %d) lenght: %d:sockfd:%d ", strerror(errno), errno,n,sockfd);
            if (sockfd != 0)
            {
                closeConnect();
            }
            if(connectPort(m_ip,m_port) ==0)
            {
                setConnectStatus(TD::ConnectSuccess);
            }
            else
            {
                closeConnect();
                m_mutex.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            continue;
        }
        // std::unique_lock<std::mutex> lk(m_mutex);
        data_analy.add(buff,n);
    }
    return 0;
}
