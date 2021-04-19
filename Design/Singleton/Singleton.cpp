#include "Singleton.h"
#include <QMutexLocker>


//Singleton* Singleton::instance = NULL;

//Singleton* Singleton::getInstance()
//{
//    if (instance == NULL)
//        instance= new Singleton;
//    return instance;
//}

//方式一（饿汉式）
//Singleton* Singleton::instance = new Singleton;
//Singleton* Singleton::getInstance(){
//    return instance;
//}
Singleton* Singleton::instance = NULL;
QMutex Singleton::m_lock;
Singleton* Singleton::getInstance()
{
   if (instance == NULL)
    {
        QMutexLocker  test(&m_lock);
        if (instance == NULL)
        {
            instance = new Singleton();
        }

    }
   return instance;
}

Singleton::Singleton()
{

}
