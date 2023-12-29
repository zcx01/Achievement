#pragma once
#include <string>
#include "tcp_define.hpp"
#include "singleton/singleton.h"

class TcpService : public Singleton<TcpService>
{
public:
    TcpService(Token token);

    void listenPortThread();

    int listenPort(int port=TCP_PORT);
};


