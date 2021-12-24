#include "text_tip_adapter.hpp" 
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../commondefine.hpp"

#define GLOBAL_CONFIG_PATH  "/opt/qt/config/icwarning_config.json"
#define CONFIG_GRADE        "grade"
#define CONFIG_FALUTMASK    "falutMask"
#define CONFIG_IMMEDIATELY  "immediately"
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
        TB_LOG_INFO("icwarning_config file no exist");
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
        TB_LOG_INFO("config file no exit topic: %s", topic.c_str());
        return;
    }

    std::string valueStr = std::to_string(value);
    std::string grade;
    WarnInfo info;
    info.topic = topic;
    info.value = value;
    try
    {
        if (config[CONFIG_GRADE].is_string())
        {
            grade = config[CONFIG_GRADE].get<std::string>();
        }
        else
        {
            grade = config[CONFIG_GRADE].get<std::map<std::string, std::string>>()[valueStr];
        }
        if (config.count(valueStr))
        {
            info.text = config[valueStr].get<std::string>();
        }

        if(config.count(CONFIG_FALUTMASK))
        {
            // auto falutMask = config.
        }

        if( WarnGrade::_from_string(grade.c_str())._to_index() == WarnGrade::W1)
        {
            info.immediately = true;
        }
        else if(config.count(CONFIG_IMMEDIATELY))
        {
            if (config[CONFIG_IMMEDIATELY].is_boolean())
            {
                info.immediately = config[CONFIG_IMMEDIATELY].get<bool>();
            }
            else
            {
                auto immediatelys = config[CONFIG_IMMEDIATELY].get<std::vector<int>>();
                info.immediately = std::find(immediatelys.begin(),immediatelys.end(),value) != immediatelys.end();
            }
        }

    }
    catch(...)
    {
        TB_LOG_INFO("value error: %s", topic.c_str());
        return;
    }
    
    bool status=m_rule.addWarnInfo(grade,info);
    TB_LOG_INFO("grade:%s text :%s topic:%s key:%d add:%d", grade.c_str(), info.text.c_str(), topic.c_str(), value,status);
}


void TextTipAdapter::sendWarnInfo(const WarnInfo &info) 
{
    TB_LOG_INFO("sendWarnInfo:%s",info.topic.c_str());   
}

