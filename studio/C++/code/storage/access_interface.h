#ifndef ACCESS_INTERFACE_H
#define ACCESS_INTERFACE_H

#include <string>
#include <map>
#include "store_info_define.h"

class AccessInterface
{
public:
    virtual ~AccessInterface(){}
    virtual std::map<std::string, StoreInfo> getData() = 0;
    virtual bool saveData(const std::map<std::string, StoreInfo> &data) = 0;
};

#endif // ACCESS_INTERFACE_H
