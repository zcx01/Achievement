#include "tcp_service_test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <thread>
#include "tcp_service.hpp"

TcpServiceTestTest::TcpServiceTestTest(/* args */) 
{
    TcpService::instance().listenPortThread();
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

CUSTOMEGISTER(TcpServiceTest,TcpServiceTestTest)