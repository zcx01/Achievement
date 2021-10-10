#ifndef STORE_INFO_DEFINE_H
#define STORE_INFO_DEFINE_H
#include <string>
#include <stdlib.h>

struct StoreInfo
{
    /* data */
    std::string value;

    void getValue(std::string &v)
    {
        v = value;
    }

    void getValue(int &v)
    {
        v=atoi(value.c_str());
    }

    void getValue(float &v)
    {
        v=atof(value.c_str());
    }

    void getValue(bool &v)
    {
        v=(bool)atoi(value.c_str());
    }

    void setValue(const std::string &v)
    {
        value = v;
    }

    template <typename T>
    void setValue(T &v)
    {
        value = std::to_string(v);
    }
};

#endif // STORE_INFO_DEFINE_H
