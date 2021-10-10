#include "text_tip_adapter.hpp"
#include "../nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../commondefine.hpp"
#include "../ObjectFactory.h"

#define GLOBAL_CONFIG_PATH  "/home/chengxiongzhu/Works/Repos/changan_c835//qt/ic_qt/resources/config/icwarning_config.json"
TextTipAdapter::TextTipAdapter() 
{
    m_rule.SetCallWarnInfoFun(std::bind(&TextTipAdapter::sendWarnInfo,this,std::placeholders::_1));
    try
    {
        nlohmann::json j;
        std::ifstream(GLOBAL_CONFIG_PATH) >> j;
        for(auto d = j.begin(); d != j.end();d++)
        {
            std::unordered_map<std::string,std::string> temp;
            for(auto iter = d.value().begin(); iter != d.value().end(); iter++)
            {
                temp[iter.key()]=iter.value();
            }
            m_data[d.key()] = temp;
        }
    }
    catch (...)
    {
        COUT("icwarning_config file no exist");
    }
}

std::unordered_map<std::string,std::string> TextTipAdapter::getData(const std::string & topic)
{
    if(m_data.count(topic) != 0)
    {
        return m_data[topic];
    }
    try
    {
        std::string topicStr = topic.substr(topic.find("/") + 1);
        if (m_data.count(topicStr) != 0)
        {
            return m_data[topicStr];
        }
    }
    catch (...)
    {
    }
    return std::unordered_map<std::string,std::string>();
}

void TextTipAdapter::addWarnInfo(std::string topic, int value) 
{
    std::unordered_map<std::string, std::string> config = getData(topic);
    if (config.empty())
    {
        COUT(topic);
        for(auto key = m_data.begin();key != m_data.end();key++)
        {
            COUT(key->first);
        }
        return;
    }
    const std::string &grade=config["grade"];
    const std::string &text=config[std::to_string(value)];
    m_rule.addWarnInfo(topic,grade,text,value);

}

void TextTipAdapter::sendWarnInfo(const WarnInfo &info) 
{
    COUT(info.topic<<"  "<<info.key<<"  "<<info.isCancel)   
}

TextTipAdapterTest::TextTipAdapterTest() 
{
    std::map<std::string,std::string> k;
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);

    d.addWarnInfo("icwarning/DoorOpenSts", 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    d.addWarnInfo("icwarning/DoorOpenSts", 0);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    

}
MYREGISTER(TextTipAdapterTest)