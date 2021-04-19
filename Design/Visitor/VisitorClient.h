#ifndef VISITORCLIENT_H
#define VISITORCLIENT_H

#include "../include/BaseClient.h"

class VisitorClient : public BaseClient
{
public:
    VisitorClient();
    ~VisitorClient();

    // BaseClient interface
public:
    void Test();
};

#endif // VISITORCLIENT_H
