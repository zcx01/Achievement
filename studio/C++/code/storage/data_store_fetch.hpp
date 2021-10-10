#pragma once
#include <string>

/**
 * @brief
 * 文件的存储和获取
 * */
#include <map>
#include <mutex>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include "store_info_define.h"
#include "../commondefine.hpp"

class AccessInterface;
class DataStoreFetch 
{

public:
    DataStoreFetch();
    ~DataStoreFetch();

    template <typename T>
    bool getValue(std::string key, T &value)
    {
        if (m_data.find(key) != m_data.end())
        {
            //不能使用 std::is_same<decltype(value), std::string>::value 判断
            //不能使用 std::is_same<T, std::string>::value 判断(C++17)
            m_data[key].getValue(value);
            return true;
        }
        return false;
    }

    template <typename T>
    bool setValue(std::string key, T &value)
    {
        StoreInfo info;
        info.setValue(value);
        m_data[key] = info;
        return dataChanged();
    }

private:
    void fetch();

    bool dataChanged();

    std::map<std::string, StoreInfo> m_data;
    AccessInterface* access = nullptr;
};

class  DataStoreFetchTest
{
public:
    DataStoreFetchTest();
    ~DataStoreFetchTest(){}
};
