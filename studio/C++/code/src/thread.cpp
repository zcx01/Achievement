#include "thread.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

bool isStop = false;
threadTest::threadTest(/* args */)
{
    time_thread = new std::thread(&threadTest::timeOut,this);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    time_thread->detach();
    delete time_thread;
    time_thread = nullptr;
    // COUT("dsssssssss")
    // isStop = true;
    // time_thread->join();
    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    COUT("135")
    // time_thread = new std::thread(&threadTest::timeOut,this);
}

void threadTest::timeOut() 
{
    int index = 0;
    while (!isStop)
    {
        COUT(index)
        index++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}


CUSTOMEGISTER(thread,threadTest)
