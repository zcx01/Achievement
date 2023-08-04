#include "ic_base_test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <thread>

class SignalMsg
{
public:
    int *signal_addr;
    bool is_timeout;
};

IcBaseTestTest::IcBaseTestTest(/* args */) 
{
    int* data = new int[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    test1 = new PolyIC::Queue();
    std::thread(&IcBaseTestTest::dealData, this).detach();


    int i = 0;
    while (1)
    {
        SignalMsg tm{data,false};
        data[0] = i;
        test1->put(PolyIC::DataMsg<SignalMsg>(0, tm));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++i;
    }
     
}

void IcBaseTestTest::dealData()
{
    while (1)
    {
        auto m = test1->get();
        auto &dm = dynamic_cast<PolyIC::DataMsg<SignalMsg> &>(*m);
        if (&dm == nullptr)
        {
            continue;
        }
        IC_LOG_INFO("dm.getPayload");
        SignalMsg sig = dm.getPayload();
        IC_LOG_INFO(sig.signal_addr[0], test1->getSize());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

CUSTOMEGISTER(IcBaseTest,IcBaseTestTest)