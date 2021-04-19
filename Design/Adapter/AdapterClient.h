#ifndef ADAPTERCLIENT_H
#define ADAPTERCLIENT_H

#include "../include/BaseClient.h"

class AdapterClient : public BaseClient
{
public:
    AdapterClient();
    ~AdapterClient();

    // BaseClient interface
public:
    void Test();
};

#endif // ADAPTERCLIENT_H
