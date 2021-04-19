#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QMetaObject>
#include <typeinfo>
#include <QDebug>

#define MYRESISCOPY(ClassName) ObjectFactory::registerClass<ClassName>(#ClassName);

class ObjectFactory
{
public:
    static ObjectFactory *getInstance();

    template<typename T> static void registerClass(QByteArray className)
    {
        constractors().insert(className,&constractorHelper<T>);
    }

    static void *createObject(const QByteArray className)
    {
        Constractor con = constractors().value(className);
        if(con == NULL)
            return NULL;
        return (*con)();
    }

private:
    ObjectFactory();

    typedef void*(*Constractor)();

    template<typename T> static void *constractorHelper()
    {
        return new T;
    }

    static QHash<QByteArray,Constractor> &constractors()
    {
        static QHash<QByteArray,Constractor> instance;
        return instance;
    }
};

template<typename T> inline static void setClassName(QByteArray className)
{
    ObjectFactory::registerClass<T>(className);
};

template<typename T> class  CMyRegister_HF
{
public:
    CMyRegister_HF(const char* className) //不能用QByteArray类型
    {
        ObjectFactory::registerClass<T>(className);
    }
};

#define MYREGISTER(ClassName)\
class CMyRegister_HF##ClassName\
{\
    private:\
    static const CMyRegister_HF<ClassName> m_staticRegister;\
};\
const CMyRegister_HF<ClassName> CMyRegister_HF##ClassName::m_staticRegister(#ClassName);\

#endif // OBJECTFACTORY_H
