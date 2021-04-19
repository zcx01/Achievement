#ifndef DESIGN_H
#define DESIGN_H
#include <QObject>

class BaseClient;

class Design
{
public:
    Design();

    static BaseClient* getClient(QByteArray funName);
};

#endif // DESIGN_H
