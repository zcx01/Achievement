#pragma once
#include <unordered_map>
#include <mutex>
#include <string>

class power_5s
{
private:
    /* data */
public:
    power_5s(/* args */);
    virtual ~power_5s(){}

    void startPower5s(bool isON);
private:
    std::unordered_map<std::string, int> m_warn_5s; // 5s加入的topic
    bool is_power_than_5 = false;
    std::mutex m_mutex;
    int time_id = 0;
};

