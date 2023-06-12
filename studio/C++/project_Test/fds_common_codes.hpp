#pragma once

#include <unordered_map>
#include <functional>
#include <initializer_list>
#include <vector>
#include "ic_log.h"

using downSigChange = std::function<void(const std::string &, const float &)>;
static std::unordered_map<std::string, std::vector<downSigChange>> downSigChanges;

using downSigChange_s = std::function<void(const std::string &, const std::string &)>;
static std::unordered_map<std::string, std::vector<downSigChange_s>> downSigChanges_s;

template <typename... T>
void DummyWrapper(T... t){};
template <typename mapFun, typename Fun>
std::string baseRegisterSigChangeFun(const std::string &topic, mapFun &mapfun, Fun fun)
{
    if (mapfun.count(topic) == 0)
    {
        std::vector<Fun> item_vec;
        item_vec.push_back(fun);
        mapfun[topic] = item_vec;
    }
    else
    {
        IC_LOG_INFO("register topic again: %s", topic.c_str());
        auto item_vec = mapfun[topic];
        item_vec.push_back(fun);
        mapfun[topic] = item_vec;
    }

    return topic;
}

template <typename FUN, typename... Ts>
void registerSigChangeFun(FUN fun, Ts... args)
{
    DummyWrapper(_registerSigChangeFun(args, fun)...);
}

template <typename mapFun, typename T>
void baseCallTopicChanged(const std::string &topic, mapFun &mapfun, const T &value)
{
    auto funs = mapfun[topic];
    for (auto fun : funs)
    {
        if (fun == nullptr)
        {
            IC_LOG_ERROR("topic no exist call: %s", topic.c_str());
            return;
        }
        fun(topic, value);
    }
}

//在.hpp实现会有多个定义,需要在.cpp中实现
std::string _registerSigChangeFun(const std::string &topic, downSigChange fun);

std::string _registerSigChangeFun(const std::string &topic, downSigChange_s fun);

void callTopicChanged(const std::string &topic, const float &value);

void callTopicChanged(const std::string &topic, const std::string &value);