#include "fds_common_codes_test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "fds_common_codes.hpp"

#define DRIVINGINFO   "DrivingInfo/IcPower"

FdsCommonCodesTestTest::FdsCommonCodesTestTest(/* args */) 
{
    FdsCommonCodesTest * test = new FdsCommonCodesTest();
    registerSigChangeFun(std::bind(&FdsCommonCodesTestTest::topic_Changed,
    this,std::placeholders::_1,std::placeholders::_2),DRIVINGINFO);

    registerSigChangeFun(std::bind(&FdsCommonCodesTestTest::topic_Changed2,
    this,std::placeholders::_1,std::placeholders::_2),DRIVINGINFO);

    registerSigChangeFun(std::bind(&FdsCommonCodesTest::topic_Changed,
    test,std::placeholders::_1,std::placeholders::_2),DRIVINGINFO);

    callTopicChanged(DRIVINGINFO,2);
}

void FdsCommonCodesTestTest::topic_Changed(std::string topic, float value)
{
    IC_LOG_INFO("topic_Changed %s: %f", topic.c_str(),value);
}

void FdsCommonCodesTestTest::topic_Changed2(std::string topic, float value)
{
    IC_LOG_INFO("topic_Changed2 %s: %f", topic.c_str(),value);
}

CUSTOMEGISTER(FdsCommonCodesTest,FdsCommonCodesTestTest)

void FdsCommonCodesTest::topic_Changed(std::string topic, float value) 
{
    IC_LOG_INFO("FdsCommonCodesTest topic_Changed2 %s: %f", topic.c_str(),value);
}
