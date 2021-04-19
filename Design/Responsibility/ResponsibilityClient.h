#ifndef RESPONSIBILITYCLIENT_H
#define RESPONSIBILITYCLIENT_H

#include "../include/BaseClient.h"

class ResponsibilityClient : public BaseClient
{
public:
    ResponsibilityClient();
    ~ResponsibilityClient();

    // BaseClient interface
public:
    void Test();
};

#endif // RESPONSIBILITYCLIENT_H
