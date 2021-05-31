#include "calenum.h"
#include <QDebug>
#include <QtMath>

CalEnum::CalEnum(QObject *parent) : QObject(parent)
{
    m_OpenOffStatus = 0;
    QList<int> res;
    res.push_back(m_OpenOffStatus);
    res.push_back(A);
    for(int i=1; i < 7;i++){
        QList<int> tmp = res;
        res.clear();
        for(auto r : tmp){
            res.push_back(r);
            res.push_back(r+std::pow(2,i));
        }
    }
    qDebug()<<calValue(A,true);
    qDebug()<<calValue(B,true);
    qDebug()<<calValue(C,true);
    qDebug()<<calValue(G,true);
    qDebug()<<calValue(G,true);
    qDebug()<<calValue(G,false);
    m_OpenOffStatus=0;
}

int CalEnum::calValue(CalEnum::OpenOffStatus s, bool add)
{
    if(add)
    {
        if(!isOpen(s))
            m_OpenOffStatus |= (int)s;
    }
    else
    {
        if(isOpen(s))
            m_OpenOffStatus = m_OpenOffStatus &~ (int)s;
    }
    return m_OpenOffStatus;
}

bool CalEnum::isOpen(CalEnum::OpenOffStatus s)
{
    return m_OpenOffStatus & s;
}
