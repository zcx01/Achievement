#pragma once

#include "vehctrl_status_item.hpp"
//{2}
class  {ClassName} : public VehctrlStatusItem
{
public:
    using VehctrlStatusItem::VehctrlStatusItem;
    void state_process(const SignalMsg &);
};
