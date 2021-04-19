#ifndef BRIDGECLIENT_H
#define BRIDGECLIENT_H

#include "../include/BaseClient.h"

class BridgeClient : public BaseClient
{
public:
    BridgeClient();
    ~BridgeClient();

    // BaseClient interface
public:
    void Test();
};

#endif // BRIDGECLIENT_H
