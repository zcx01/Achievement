#pragma once
#include <string>
#include <unordered_map>

namespace fds
{
    std::unordered_map<std::string,std::string> getTopicSigName()
    {
        static std::unordered_map<std::string,std::string> content;
        if(!content.empty()) return content;
        content["JIUsdsa"] = "dsdsasdd";
        return content;
    }

    std::unordered_map<std::string,std::string> getSigNameTopic()
    {
        static std::unordered_map<std::string,std::string> content;
        if(!content.empty()) return content;
        content["JIUsdsa"] = "dsdsasdd";
        return content;
    }

}