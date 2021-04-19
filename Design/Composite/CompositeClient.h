#ifndef COMPOSITECLIENT_H
#define COMPOSITECLIENT_H

#include "../include/BaseClient.h"

class CompositeClient : public BaseClient
{
public:
    CompositeClient();
    ~CompositeClient();

    // BaseClient interface
public:
    void Test();
};

#endif // COMPOSITECLIENT_H
