#include "tcp_client.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
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

TcpClientTest::TcpClientTest(/* args */) 
{
    connectPort("127.0.0.1",6666);
    while (1)
    {
        char sendline[MAXLINE];
        IC_LOG_INFO("send msg to server:");
        fgets(sendline, 4096, stdin);
        IC_LOG_INFO("send:%u",sendline);
        if (send(sockfd, sendline, strlen(sendline), 0) < 0)
        {
            IC_LOG_INFO("send msg error: %s(errno: %d)", strerror(errno), errno);
        }
    }
}

TcpClientTest::~TcpClientTest() 
{
    if(sockfd != 0) close(sockfd);
}

int TcpClientTest::connectPort(std::string ip, int port) 
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

CUSTOMEGISTER(TcpClient,TcpClientTest)
