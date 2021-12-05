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
            std::unordered_map<std::string, nlohmann::json> temp;
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

std::unordered_map<std::string,nlohmann::json>  TextTipAdapter::getData(const std::string & topic)
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
    return std::unordered_map<std::string,nlohmann::json>();
}

void TextTipAdapter::addWarnInfo(std::string topic, int value) 
{
    std::unordered_map<std::string, nlohmann::json> config = getData(topic);
    if (config.empty())
    {
        COUT("config file no exit topic: %s"<< topic.c_str());
        return;
    }

    WarnInfo info;
    info.topic = topic;
    info.value = value;
    const std::string &grade=config["grade"].get<std::string>();
    try
    {
        info.text =config[std::to_string(value)].get<std::string>();
    }
    catch(...)
    {
    }
    
    bool status=m_rule.addWarnInfo(grade,info);
}

void TextTipAdapter::sendWarnInfo(const WarnInfo &info) 
{
    COUT(info.topic<<"  "<<info.value<<"  "<<info.isCancel)   
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