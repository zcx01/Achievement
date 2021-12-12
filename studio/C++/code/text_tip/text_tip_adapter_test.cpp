#include "text_tip_adapter_test.hpp"
#include "../commondefine.hpp"
#include "../ObjectFactory.h"
#include <fstream>

TextTipAdapterTest::TextTipAdapterTest()
{
    d.m_rule.SetCallWarnInfoFun(std::bind(&TextTipAdapterTest::sendWarnInfo, this, std::placeholders::_1));
    OneTest();
}

void TextTipAdapterTest::OneTest()
{
    is_one_finish = true; 
    for (auto iter = d.m_data.begin(); iter != d.m_data.end(); iter++)
    {
        auto topic = (*iter).first;
        for (auto iter_value = (*iter).second.begin(); iter_value != (*iter).second.end(); iter_value++)
        {
            try
            {
                auto value_str = (*iter_value).first;
                int value = std::atoi(value_str.c_str());
                if(value == 0) continue;
                addWarn(topic, value);
            }
            catch(const std::exception& e)
            {
            }
        }
        addWarn(topic, 0);
        is_one_finish = true; 
    }
}

void TextTipAdapterTest::addWarn(std::string topic, int value) 
{
    while (!is_one_finish)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    d.addWarnInfo(topic, value);
    is_one_finish = false;
}

void TextTipAdapterTest::sendWarnInfo(const WarnInfo &info)
{
    TB_LOG_INFO("TextTipAdapterTest :%s", info.topic.c_str() ,info.text.c_str() , d.m_rule.getAlreadyTime());
    if (info.text.empty()  || info.isCancel)
    {
        is_one_finish = true;
    }
}

MYREGISTER(TextTipAdapterTest)