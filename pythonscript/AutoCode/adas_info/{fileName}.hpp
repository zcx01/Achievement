#pragma once

#include "adas_info_item.hpp"
#include "parser_can_api.h"

class {ClassName} : public AdasInfoItem
{
public:
    using AdasInfoItem::AdasInfoItem;
    void state_process(const SignalMsg &);

private:    

};

