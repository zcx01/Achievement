#ifndef OBSERVERCLIENT_H
#define OBSERVERCLIENT_H

#include "../include/BaseClient.h"

class ObserverClient : public BaseClient
{
public:
    ObserverClient();
    ~ObserverClient();

    // BaseClient interface
public:
    void Test();
};

#endif // OBSERVERCLIENT_H
