#ifndef PROXYCLIENT_H
#define PROXYCLIENT_H

#include "../include/BaseClient.h"

class ProxyClient : public BaseClient
{
public:
    ProxyClient();

    // BaseClient interface
public:
    void Test();
};

#endif // PROXYCLIENT_H
