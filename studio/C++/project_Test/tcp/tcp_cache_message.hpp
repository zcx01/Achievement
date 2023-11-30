#pragma once

#include "tcp_receive.hpp"
#include "fds_cpp_timer.hpp"
#include <unordered_map>

#define RESENDCOUNT 3
#define RESENDTIME 2000 // 20s


class TcpCacheMessage : public TcpReceive
{
public:
    TcpCacheMessage(/* args */);
    virtual ~TcpCacheMessage();

    void addMessage(uint8_t* msgData, int msgLenght);
private:
    struct CacheData
    {
        std::vector<uint8_t> msgData;
        int count = RESENDCOUNT;
        CacheData(){}
        CacheData(const std::vector<uint8_t> &d){msgData =d;}
    };
    
    /* data */
    bool onMessageDataAndBodyArrival(MessageData msgData, MessageBody msgBody) override;

    void timeOut(int timerId);

    std::unordered_map<uint64_t,CacheData> m_CacheDatas;
    std::unordered_map<uint64_t, int> m_timerId;
    fds::fds_cpp_timer* m_timer = nullptr;
};


