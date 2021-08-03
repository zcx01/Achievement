#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <list>

#define MYRESISCOPY(ClassName) ObjectFactory::registerClass<ClassName>(#ClassName);

class ObjectFactory
{
public:
    static ObjectFactory *getInstance();

    template<typename T> static void registerClass(std::string className)
    {
        constractors()[className]=&constractorHelper<T>;
    }

    static void *createObject(const std::string className)
    {
        Constractor con = constractors()[className];
        if(con == NULL)
            return NULL;
        return (*con)();
    }

    static void getObjectName(std::list<std::string> &names)
    {
        names.clear();
        for(auto iter = constractors().begin(); iter != constractors().end(); iter++)
        {
            names.push_back(iter->first);
        }
    }  
private:
    ObjectFactory();

    typedef void*(*Constractor)();

    template<typename T> static void *constractorHelper()
    {
        return new T;
    }

    static std::unordered_map<std::string,Constractor> &constractors()
    {
        static std::unordered_map<std::string,Constractor> instance;
        return instance;
    }
};

template<typename T> inline static void setClassName(std::string className)
{
    ObjectFactory::registerClass<T>(className);
};

template<typename T> class CRegister
{
public:
    CRegister(const char* className) //不能用QByteArray类型
    {
        ObjectFactory::registerClass<T>(className);
    }
};

#define MYREGISTER(ClassName) CUSTOMEGISTER(ClassName,ClassName)

#define CUSTOMEGISTER(Name,ClassName)\
class CRegister##Name\
{\
    private:\
    static const CRegister<ClassName> m_staticRegister;\
};\
const CRegister<ClassName> CRegister##Name::m_staticRegister(#Name);

#endif // OBJECTFACTORY_H
