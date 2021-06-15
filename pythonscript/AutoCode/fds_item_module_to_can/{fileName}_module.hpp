#ifndef  {FILENAME}_MODULE_HPP
#define {FILENAME}_MODULE_HPP

#include <map>
#include <set>
#include "base_fds_module.hpp"
#include "air_conditioner.hpp"
#include "charger.hpp"
#include "interface/listener/pubsub_listener_interface.h"
#include "{fileName}_item.hpp"


using std::string;
using namespace megaipc;


class {ClassName}Module final: public PubSubListenerInterface, public std::enable_shared_from_this<{ClassName}Module>
{

private:
    std::map<std::string, std::set<std::shared_ptr<{ClassName}Item>>> topic_items_map;

public:
    /**
     * @brief 启动FDS 处理下行控制指令
     */
    void start();

    /**
     * @brief 添加 Topic 与 FDS功能项 的映射关系
     * @param  signal           CAN信号
     * @param  item             FDS功能项实现
     */
    void add_item(const string &topic, std::shared_ptr<{ClassName}Item> item);

    /**
     * @brief 为map中的信号和FDS实现 创建连接关系
     * @param 
     */
    void link_topic_item_module(std::map<std::string, std::set<std::shared_ptr<{ClassName}Module>>>& signal_modules_map);

    // PubSubListenerInterface interface
    void onMessageArrival(const string &topic, const IpcMessage &msg);
    void onMessageDelivered(const string &msgId);
    void onConnectStateChanged(const string &nodeId, const ConnectState &state);

private:
    void link_signal_item();

    std::shared_ptr<AirConditioner> air_conditioner = nullptr;
};

#endif // !{FILENAME}_MODULE_HPP
