#ifndef PROTOTYPECLIENT_H
#define PROTOTYPECLIENT_H

#include "../include/BaseClient.h"

class PrototypeClient : public BaseClient
{
public:
    PrototypeClient();
    ~PrototypeClient();

    // BaseClient interface
public:
    void Test();
};

#endif // PROTOTYPECLIENT_H
