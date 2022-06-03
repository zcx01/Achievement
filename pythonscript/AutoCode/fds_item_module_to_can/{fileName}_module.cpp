#include "{fileName}_module.hpp"
#include "base_library.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_def.h"


void {ClassName}Module::start()
{
    auto api = MegaIpcApi::createInstance();
    api->init();
    for (auto &it:topic_items_map)
    {
        api->subscribe(it.first);
    }
    api->setListener(this);
}

void {ClassName}Module::add_item(const string &topic, std::shared_ptr<{ClassName}Item> item)
{
    if (topic_items_map.count(topic) == 0)
    {
        auto item_set = std::make_shared<std::set<std::shared_ptr<{ClassName}Item>>>();
        item_set->emplace(item);
        topic_items_map[topic] = *item_set;
    }
    else
    {
        auto item_set = topic_items_map[topic];
        item_set.emplace(item);
        topic_items_map[topic] = item_set;
    }
}

void {ClassName}Module::link_topic_item_module(std::map<std::string, std::set<std::shared_ptr<{ClassName}Module>>> &topic_modules_map)
{
    link_signal_item();

    auto topic_set = std::make_shared<std::set<std::string>>();

    for (auto &it : topic_items_map)
    {
        topic_set->emplace(it.first);
    }

    for (auto &topic : *topic_set)
    {
        if (topic_modules_map.count(topic) == 0)
        {
            auto module_set = std::make_shared<std::set<std::shared_ptr<{ClassName}Module>>>();
            module_set->emplace(shared_from_this());
            topic_modules_map[topic] = *module_set;
        }
        else
        {
            auto module_set = topic_modules_map[topic];
            module_set.emplace(shared_from_this());
            topic_modules_map[topic] = module_set;
        }
    }
}

void {ClassName}Module::onMessageArrival(const string &topic, const IpcMessage &msg)
{
    IC_LOG_INFO("onMessageArrival: %s, %s", topic.data(), msg.data);
    std::string content((char *)msg.data, msg.length);

    if (topic_items_map.count(topic) == 0)
        return;

    auto vehctrl_set = topic_items_map[topic];
    for (auto &item : vehctrl_set)
    {
        item->state_process(topic, content);
    }
}

void {ClassName}Module::onMessageDelivered(const string &msgId)
{
    IC_LOG_INFO("onMessageDelivered: %s", msgId.data());
}

void {ClassName}Module::onConnectStateChanged(const string &nodeId, const ConnectState &state)
{
    IC_LOG_INFO("onConnectStateChanged: %s, %d", nodeId.data(), state);
}

void {ClassName}Module::link_signal_item()
{


}
