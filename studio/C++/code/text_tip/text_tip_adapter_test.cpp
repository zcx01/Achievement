#include "text_tip_adapter_test.hpp"
#include "../commondefine.hpp"
#include "../ObjectFactory.h"
#include <fstream>

std::vector<std::string> str_split(const std::string &strtem, const std::string &a)
{
    std::vector<std::string> strvec;

    std::string::size_type pos1, pos2;
    pos2 = strtem.find(a);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        strvec.push_back(strtem.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = strtem.find(a, pos1);
    }
    strvec.push_back(strtem.substr(pos1));
    return strvec;
}

TextTipAdapterTest::TextTipAdapterTest()
{
    d.m_rule.SetCallWarnInfoFun(std::bind(&TextTipAdapterTest::sendWarnInfo, this, std::placeholders::_1));
    add_Test_Topic();
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
                if (value == 0)
                    continue;
                addWarn(topic, value);
            }
            catch (const std::exception &e)
            {
            }
        }
        addWarn(topic, 0);
        is_one_finish = true;
    }
}

void TextTipAdapterTest::add_Test_Topic()
{
    COUT_Topic();
    while (true)
    {
        std::string c1;
        std::getline(std::cin, c1, '\n');
        if (c1.find("-h") != std::string::npos)
        {
            COUT_Topic();
        }
        else
        {
            auto cs = str_split(c1, " ");
            if (cs.size() < 2)
            {
                COUT("参数大小输入不合法");
                continue;
            }
            d.addWarnInfo(cs[0], std::atoi(cs[1].c_str()));
        }
    }
}

void TextTipAdapterTest::COUT_Topic()
{
    for (auto iter = d.m_data.begin(); iter != d.m_data.end(); iter++)
    {
        auto topic = (*iter).first;
        for (auto iter_value = (*iter).second.begin(); iter_value != (*iter).second.end(); iter_value++)
        {
            try
            {
                auto value_str = (*iter_value).first;
                int value = std::atoi(value_str.c_str());
                if (value == 0)
                    continue;
                TB_LOG_INFO(topic, value, (*iter_value).second);
            }
            catch (const std::exception &e)
            {
            }
        }
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
    TB_LOG_INFO("TextTipAdapterTest ", info.topic.c_str(), info.text.c_str(),info.alreadyTime);
    if (info.text.empty() || info.isCancel) 
    {
        is_one_finish = true;
    }
}

MYREGISTER(TextTipAdapterTest)