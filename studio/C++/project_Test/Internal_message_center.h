#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include "ic_log.h"


#define CALLREGISTERFUN lock.unlock(); fun(topic, value); lock.lock();
namespace fds
{
    using downSigChange = std::function<void(const std::string &, const float &)>;
    static std::unordered_map<std::string, std::vector<downSigChange>> downSigChanges;
    static std::unordered_map<std::string, float> downSigValues;

    using downSigChange_s = std::function<void(const std::string &, const std::string &)>;
    static std::unordered_map<std::string, std::vector<downSigChange_s>> downSigChanges_s;
    static std::unordered_map<std::string, std::string> downSigValues_s;

    static std::mutex value_mutex;

    template <typename... T>
    void DummyWrapper(T... t){};
    template <typename mapFun, typename Fun,typename mapValue>
    std::string baseRegisterSigChangeFun(const std::string &topic, mapFun &mapfun, Fun fun,mapValue &mapvalue)
    {
        std::unique_lock<std::mutex> lock(value_mutex);
        if (mapfun.count(topic) == 0)
        {
            std::vector<Fun> item_vec;
            item_vec.push_back(fun);
            mapfun[topic] = item_vec;
        }
        else
        {
            auto item_vec = mapfun[topic];
            item_vec.push_back(fun);
            mapfun[topic] = item_vec;
        }

        if(mapvalue.count(topic) != 0 && fun != nullptr)
        {
            auto value = mapvalue[topic];
            CALLREGISTERFUN
        }
        return topic;
    }
    std::string _registerSigChangeFun(const std::string &topic, downSigChange fun);

    std::string _registerSigChangeFun(const std::string &topic, downSigChange_s fun);

    template <typename FUN, typename... Ts>
    void registerSigChangeFun(FUN fun, Ts... args)
    {
        DummyWrapper(_registerSigChangeFun(args, fun)...);
    }

    template <typename mapFun, typename T,typename mapValue>
    void baseCallTopicChanged(const std::string &topic, mapFun &mapfun,mapValue &mapvalue, const T &value)
    {
        std::unique_lock<std::mutex> lock(value_mutex);
        auto funs = mapfun[topic];
        for (auto fun : funs)
        {
            if (fun == nullptr)
            {
                return;
            }
            CALLREGISTERFUN
        }
        
        mapvalue[topic] = value;
    }

    template <typename T,typename mapValue>
    bool baseGetTopicValue(const std::string &topic,mapValue &mapvalue,T &value)
    {
        std::unique_lock<std::mutex> lock(value_mutex);
        if(mapvalue.count(topic) != 0)
        {
            value = mapvalue[topic];
            return true;
        }
        return false;
    }


    void callTopicChanged(const std::string &topic, const float &value);

    void callTopicChanged(const std::string &topic, const std::string &value);

    bool getTopicValue(const std::string &topic,float &value);

    bool getTopicValue(const std::string &topic,std::string &value);
} // namespace fds
