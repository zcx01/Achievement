/**
 * @file vehctrl_item.hpp
 * @brief {ClassName}Item definition
 * @date 2021-05-17
 * @copyright Copyright (c) 2021 Megatronix
 */
#ifndef {FILENAME}_ITEM_HPP
#define {FILENAME}_ITEM_HPP

#include <string>
#include <memory>
#include "base_library.h"

using std::string;
class {ClassName}Module;

/**
 * @brief 车控FDS功能项
 * 定义了处理车控FDS的逻辑 需要实现的虚函数
 */
class {ClassName}Item : public std::enable_shared_from_this<{ClassName}Item>
{

public:
    /**
     * @brief 从{ClassName}Module::signal_items_map 订阅 topic
     * @param  topic      车控命令topic
     */
    void subscribe(const std::string& topic);
    {ClassName}Item(std::shared_ptr<{ClassName}Module> module);

    /**
     * @brief 抽象的车控信号处理函数
     */
    virtual void state_process(const std::string &topic, const std::string& content) = 0;
    std::shared_ptr<{ClassName}Module> module = nullptr;
};

#endif // !{FILENAME}_ITEM_HPP
