#ifndef FLYWEIGHTCLIENT_H
#define FLYWEIGHTCLIENT_H

#include "../include/BaseClient.h"

class FlyweightClient : public BaseClient
{
public:
    FlyweightClient();
    ~FlyweightClient();

    // BaseClient interface
public:
    void Test();
};

#endif // FLYWEIGHTCLIENT_H
