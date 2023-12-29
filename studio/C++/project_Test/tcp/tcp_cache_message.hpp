#pragma once

#include "tcp_receive.hpp"
#include "fds_cpp_timer.hpp"
#include <unordered_map>

#define RESENDCOUNT 3
#define RESENDTIME 2000 // 20s


class TcpCacheMessage : public TcpBaseReceive
{
public:
    TcpCacheMessage(/* args */);
    virtual ~TcpCacheMessage();

    void addMessage(uint8_t* data, int lenght);
private:
    struct CacheData
    {
        std::vector<uint8_t> msgData;
        int count = RESENDCOUNT;
        CacheData(){}
        CacheData(const std::vector<uint8_t> &d){msgData =d;}
    };
    
    /* data */
    virtual bool onAppDataArrival(uint8_t *app_data, int app_lenght);

    virtual uint32_t getType();

    bool removeId(uint64_t msgId);

    void timeOut(int timerId);

    std::unordered_map<uint64_t,CacheData> m_CacheDatas;
    std::unordered_map<uint64_t, int> m_timerId;
    fds::fds_cpp_timer* m_timer = nullptr;
};


