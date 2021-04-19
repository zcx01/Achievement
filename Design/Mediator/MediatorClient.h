#ifndef MEDIATORCLIENT_H
#define MEDIATORCLIENT_H

#include "../include/BaseClient.h"

class MediatorClient : public  BaseClient
{
public:
    MediatorClient();
    ~MediatorClient();

    // BaseClient interface
public:
    void Test();
};

#endif // MEDIATORCLIENT_H
