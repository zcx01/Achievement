#ifndef INTERPERTERCLIENT_H
#define INTERPERTERCLIENT_H

#include "../include/BaseClient.h"

class InterperterClient : public BaseClient
{
public:
    InterperterClient();
    ~InterperterClient();

    // BaseClient interface
public:
    void Test();
};

#endif // INTERPERTERCLIENT_H
