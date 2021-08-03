#pragma once

#include "vehctrl_item.hpp"
//{3}
namespace vehctrl
{

class {ClassName} : public VehCtrlItem
{
public:
    using VehCtrlItem::VehCtrlItem;
    void state_process(const std::string &topic, const std::string &content);
};

}