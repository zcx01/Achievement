#pragma once
#include <string>

class FdsCommonCodesTestTest
{
private:
    /* data */
public:
    FdsCommonCodesTestTest(/* args */);

    void topic_Changed(std::string topic,float value);

    void topic_Changed2(std::string topic,float value);
};

class FdsCommonCodesTest
{
private:
    /* data */
public:
    FdsCommonCodesTest(/* args */){}

    void topic_Changed(std::string topic,float value);
};
