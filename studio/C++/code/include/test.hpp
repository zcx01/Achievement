#pragma once
#include <string>
#include "fds_time_out_process.hpp"

class TestTest
{
private:
    /* data */
public:
    TestTest(/* args */);

    void thread_Test(float value);

    std::shared_ptr<FdsTimeOutProcess> time_out_process = nullptr;
    int count=0;
};

