#pragma once

#include "uartrpc_svc7_item.hpp"
//{3}
namespace UARTPC
{

class {ClassName} : public UartrpcSvc7Item
{
public:
    using UartrpcSvc7Item::UartrpcSvc7Item;
    void state_process(const std::string &topic, const std::string &content);
    void deal_process(const std::string &topic, const IpcMessage &msg);
};

}