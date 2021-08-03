#pragma once

#include "drvinfo_item.hpp"
#include "parser_can_api.h"

class {ClassName} : public DrvInfoItem
{
public:
    using DrvInfoItem::DrvInfoItem;
    void state_process(const SignalMsg &);

private:    
    void publishValue(float value,std::string topic);

    void signalChange(float value,std::string topic);
    
    void publishInvalid(std::string topic);
};

