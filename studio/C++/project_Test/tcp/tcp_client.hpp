#pragma once
#include <string>
#include "tcp_define.hpp"
#include "tcp_data_analy.hpp"
#include "singleton/singleton.h"
#include "queue.h"
#include <mutex>

using namespace TD;

class TcpClient : public Singleton<TcpClient> 
{
public:
    TcpClient(Token token);
    ~TcpClient();

    void init();

    //异步连接
    void startConnectThread(std::string ip = TCP_IP ,int port = TCP_PORT);

    void closeConnect();

    void sendMsg(uint8_t *data, int msgLenght);

    void addCallFun(RecDataFun fun);

private:
    //同步连接
    void connectSocket(std::string ip = TCP_IP ,int port = TCP_PORT);


    void onMessageArrival(uint8_t *msg, int lenght);

    int receiveMsg();

    void setConnectStatus(TcpConnectStatus status);

    int connectPort(std::string ip,int port);

    void setSendStatus(const TcpSendStatus & status);

    TcpDataAnaly data_analy;

    std::vector<RecDataFun> m_funs;

    int sockfd = 0;

    bool is_exitReceiveMsg = true;

    std::mutex m_mutex;
};