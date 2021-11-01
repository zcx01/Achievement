#pragma once
#include <string>
#include <thread>

class threadTest
{
private:
    /* data */
public:
    threadTest(/* args */);

    void timeOut();

    std::thread * time_thread;
};

