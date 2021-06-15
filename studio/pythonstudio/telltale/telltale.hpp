#pragma once

#include "lamp_item.hpp"

class  {ClassName} : public LampItem
{
public:
    using LampItem::LampItem;
    void state_process(const SignalMsg &);

private:
    enum result_type
    {
        LAMP_OFF = 0,
        LAMP_ON,
    };
    result_type normal_logic(int power, int signal);
};
