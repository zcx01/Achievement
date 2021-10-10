#include "chimeTest.hpp"
#include "../ObjectFactory.h"
#include "../commondefine.hpp"
#include <iostream>

ChimeTestTest::ChimeTestTest(/* args */) 
{
    megaipc::ChimePlayInfo info;
    info.id = LOW_KEY_POWER;
    info.playValues.push_back(info.state);
    play.play_contorl(info);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // play.play_contorl(info);
    }
}

CUSTOMEGISTER(ChimeTest,ChimeTestTest)