#include "fds_common_codes.hpp"

std::string _registerSigChangeFun(const std::string &topic, downSigChange fun)
{
    return baseRegisterSigChangeFun(topic, downSigChanges, fun);
}

std::string _registerSigChangeFun(const std::string &topic, downSigChange_s fun)
{
    return baseRegisterSigChangeFun(topic, downSigChanges_s, fun);
}

void callTopicChanged(const std::string &topic, const float &value)
{
    baseCallTopicChanged(topic, downSigChanges, (float)value);
}

void callTopicChanged(const std::string &topic, const std::string &value)
{
    baseCallTopicChanged(topic, downSigChanges_s, value);
}