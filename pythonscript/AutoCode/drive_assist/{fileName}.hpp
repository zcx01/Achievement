#pragma once

#include "drive_assist_item.hpp"
//{3}
namespace DriveAssist
{

class {ClassName} : public DriveAssistItem
{
public:
    using DriveAssistItem::DriveAssistItem;
    void state_process(const std::string &topic, const std::string &content);
};

}