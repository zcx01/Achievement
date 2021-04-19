#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H
#include <QHash>

//Flyweight类，它是所有具体享元类的超类或接口,通过这个接口，Flyweight可以接收并作用于外部状态
class Flyweight
{
public:
    Flyweight();
    virtual void Operation(int extrinsicstate) =0;
};

//ConcreteFlyweight是继承Flyweight超类或实现Flyweight接口，并为内部状态增加储存空间
class ConcreteFlyweight : public Flyweight
{
    // Flyweight interface
public:
    void Operation(int extrinsicstate);
};

//UnSharedConcreteFlyweight是指那些不要需共享的Flyweight子类。因为Flyweight接口共享成为可能，但是它不强制共享
class UnSharedConcreteFlyweight : public Flyweight
{
    // Flyweight interface
public:
    void Operation(int extrinsicstate);
};

//FlyweightFactory,是一个享元工厂,用来创建并管理Flyweight对象。它主要是用来确保合理地共享Flyweight,
//当用户请求一个Flyweight时,FlyweightFactory对象提供一个创建的实例或者创建一个(如果不存在的话)
class FlyweightFactory
{
public:
    FlyweightFactory();

    Flyweight* getFlyweight(QString key);
private:
    QHash<QString,Flyweight*> m_Flyweights;
};

#endif // FLYWEIGHT_H
