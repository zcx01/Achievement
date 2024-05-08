#include "tcp_service.hpp"
#include "ic_log.h"
#include <iostream>


#include<thread>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

/* *
 * 参考
 * https://segmentfault.com/a/1190000010838127
 * https://www.cnblogs.com/zkfopen/p/9441264.html
 * 
 * */

TcpService::TcpService(Token token) 
{
}

void TcpService::listenPortThread()
{
    std::thread(&TcpService::listenPort,this,TCP_PORT).detach();
}

int TcpService::listenPort(int port) 
{
    int listenfd, connfd=0;
    struct sockaddr_in servaddr;
    char buff[MAX_LENGHT];
    int n = 0;

    /* **
     * AF_INET:IPv4、 AF_INET6:IPv6
     * SOCK_STREAM:TCP SOCK_DGRAM:UDP
     * */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        IC_LOG_INFO("create socket error: %s(errno: %d)", strerror(errno), errno);
        return -1;
    }

    IC_LOG_INFO("----init socket----");


    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//也可以是ip地址
    servaddr.sin_port = htons(port);

        // 设置端口复用。
    int optval = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        IC_LOG_INFO("bind socket error: %s(errno: %d)", strerror(errno), errno);
        return -1;
    }
    IC_LOG_INFO("----bind sucess----");

    //sockfd:绑定了地址的socket文件描述符。
    //backlog:服务器负载，提示系统进程所要入队的未完成请求数量
    if (listen(listenfd, 10) == -1)
    {
        IC_LOG_INFO("listen socket error: %s(errno: %d)", strerror(errno), errno);
        return -1;
    }

    IC_LOG_INFO("======waiting for client's request======");

    if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1)
    {
        IC_LOG_INFO("accept socket error: %s(errno: %d)", strerror(errno), errno);
    }
    while(1)
    {
        if(connfd != 0)
        {
            n = recv(connfd, buff, MAX_LENGHT, 0);
        }
        if(n <= 0 && errno != EINTR && connfd !=0)
        {
            close(connfd);
            connfd = 0;
            if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1)
            {
                IC_LOG_INFO("accept socket error: %s(errno: %d)", strerror(errno), errno);
            }
            continue;
        }
        TD::printHex("service",(uint8_t*)buff,n);
        write(connfd, buff, n);
    }
    IC_LOG_INFO("close:%u",listenfd);
    close(connfd);
    close(listenfd);
    return 0;
}
