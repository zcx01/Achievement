#include "thread.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

bool isStop = false;
threadTest::threadTest(/* args */)
{
    time_thread = new std::thread(&threadTest::timeOut,this);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // time_thread->join();
    // delete time_thread;
    COUT("dsssssssss")
    isStop = true;
    time_thread->join();
    COUT("135")
    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    // time_thread = new std::thread(&threadTest::timeOut,this);
}

void threadTest::timeOut() 
{
    int index = 0;
    while (!isStop)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        COUT(index)
        index++;
    }
    
}


CUSTOMEGISTER(thread,threadTest)
