#include "access_json.h"
#include "../nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../commondefine.hpp"

//"file:///home/chengxiongzhu/Works/Repos/changan_c385/qt/ic_qt/resources/config/ictelltale_config.json"
#define DATAJSONFILE "/home/chengxiongzhu/Works/Repos/changan_c385/qt/ic_qt/resources/config/ictelltale_configs.json"
std::map<std::string, StoreInfo> AccessJson::getData() 
{
    std::map<std::string, StoreInfo> data;
    try
    {
        nlohmann::json j;
        std::ifstream(DATAJSONFILE) >> j;
        COUT(j)
        for(auto d = j.begin(); d != j.end();++d)
        {
            StoreInfo info;
            info.value = d.value();
            data[d.key()] = info;
            COUT(data[d.key()].value)
        }
        // COUTMAP(data);
    }
    catch (...)
    {
        COUT("类型错误");
    }
    return data;
}

bool AccessJson::saveData(const std::map<std::string, StoreInfo> &data) 
{
    std::ofstream of(DATAJSONFILE);
    nlohmann::json j;
    for(auto iter : data)
    {
        j[iter.first] = iter.second.value;
    }
    of << std::setw(4) << j <<std::endl;
    return false;
}
