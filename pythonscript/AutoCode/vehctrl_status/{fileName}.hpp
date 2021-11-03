#pragma once
#include "vehctrl_status_item.hpp"
#include <map>


class  {ClassName} : public VehctrlStatusItem
{
public:
    using VehctrlStatusItem::VehctrlStatusItem;
    void state_process(const SignalMsg &);
    void addSignalAndTop(struct veh_signal* s,const std::string &t);
    

private:

    void publish_status(const std::string &topic, float value,bool isVaild);
    std::string topic;
    struct veh_signal * signal=nullptr;
};
