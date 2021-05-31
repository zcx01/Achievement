#ifndef CALENUM_H
#define CALENUM_H

#include <QObject>

class CalEnum : public QObject
{
    Q_OBJECT

public:
    enum OpenOffStatus{
        A=0x01,
        B=0x02,
        C=0x04,
        D=0x08,
        E=0x10,
        F=0x20,
        G=0x40
    };
    Q_ENUMS(OpenOffStatus)
    explicit CalEnum(QObject *parent = nullptr);

    Q_INVOKABLE int calValue(OpenOffStatus s,bool add);

    Q_INVOKABLE bool isOpen(OpenOffStatus s);
signals:

private:
    int m_OpenOffStatus;
};

#endif // CALENUM_H
