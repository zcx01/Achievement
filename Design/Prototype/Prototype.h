#ifndef PROTOTYPE_H
#define PROTOTYPE_H
#include <QObject>

class Prototype
{
public:
    Prototype(QString str);

    QString getStr();

    void setStr(QString str);

    virtual Prototype* clone() = 0;

private:
    QString m_Str;
};


class ConcretePrototype1 : public Prototype
{
public:
    ConcretePrototype1(QString id);

    Prototype *clone();
};

#endif // PROTOTYPE_H
