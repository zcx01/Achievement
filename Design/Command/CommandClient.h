#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include "../include/BaseClient.h"

class CommandClient : public BaseClient
{
public:
    CommandClient();
    ~CommandClient();

    // BaseClient interface
public:
    void Test();
};

#endif // COMMANDCLIENT_H
