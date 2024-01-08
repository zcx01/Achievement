#include "Internal_message_center.h"

void fds::callTopicChanged(const std::string &topic, const float &value)
{
    baseCallTopicChanged(topic, downSigChanges,downSigValues, (float)value);
}

void fds::callTopicChanged(const std::string &topic, const std::string &value)
{
    baseCallTopicChanged(topic, downSigChanges_s,downSigValues_s,value);
}

bool fds::getTopicValue(const std::string &topic, float &value)
{
    return baseGetTopicValue(topic,downSigValues,value);
}

bool fds::getTopicValue(const std::string &topic, std::string &value)
{
    return baseGetTopicValue(topic,downSigValues_s, value);
}

std::string fds::_registerSigChangeFun(const std::string &topic, downSigChange fun)
{
    return baseRegisterSigChangeFun(topic, downSigChanges, fun,downSigValues);
}

std::string fds::_registerSigChangeFun(const std::string &topic, downSigChange_s fun)
{
    return baseRegisterSigChangeFun(topic, downSigChanges_s, fun,downSigValues_s);
}
