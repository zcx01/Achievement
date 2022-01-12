#pragma once

#include "chime_item.hpp"
//{3}
class  {ClassName} : public ChimeItem
{
public:
    using ChimeItem::ChimeItem;
    void state_process(const SignalMsg &);

private:
    void send(const std::string &topic,const int &value);

};
