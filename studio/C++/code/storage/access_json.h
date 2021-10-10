#ifndef ACCESS_JSON_H
#define ACCESS_JSON_H
#include "access_interface.h"

class AccessJson : public AccessInterface
{
public:
    std::map<std::string, StoreInfo> getData() override;
    bool saveData(const std::map<std::string, StoreInfo> &data) override;
};

#endif // ACCESS_JSON_H
