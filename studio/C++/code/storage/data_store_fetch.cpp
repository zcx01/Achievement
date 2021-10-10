#include "data_store_fetch.hpp"
#include <iostream>
#include "access_json.h"
#include "../ObjectFactory.h"

DataStoreFetch::DataStoreFetch() 
{
    access = new AccessJson();
    fetch();
}

DataStoreFetch::~DataStoreFetch() 
{
    if(access)
    {
        delete access;
        access=nullptr;
    }
}

bool DataStoreFetch::dataChanged()
{
    if (access)
    {
       return access->saveData(m_data);
    }
    return false;
}

void DataStoreFetch::fetch()
{
    if(access)
    {
        m_data=access->getData();
    }
}

DataStoreFetchTest::DataStoreFetchTest() 
{
    DataStoreFetch d;
    float value=0;
    COUT(d.getValue("left1111",value));
    COUT(value)

    value=500;
    d.setValue("left",value);
}
MYREGISTER(DataStoreFetchTest)