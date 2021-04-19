#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>
class Singleton
{
public:

    static Singleton* getInstance();
private:

    Singleton();

    //把复制构造函数和=操作符也设为私有,防止被复制

    Singleton(const Singleton&);

    Singleton& operator=(const Singleton&);

    static Singleton* instance;
    static QMutex m_lock;

};

#endif // SINGLETON_H
