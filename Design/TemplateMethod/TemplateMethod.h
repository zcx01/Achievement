#ifndef TEMPLATEMETHOD_H
#define TEMPLATEMETHOD_H

class AbstractClass
{
public:
    //一些抽象行为，放到子类去实现
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;

    //模板方法，给出了逻辑的骨架，而逻辑的组成是一些相对应的抽象操作，它们都推迟到子类实现
    void TemplateMethod();
};

class ConcreteClassA : public AbstractClass
{
    // AbstractClass interface
public:
    void PrimitiveOperation1();
    void PrimitiveOperation2();
};

class ConcreteClassB : public AbstractClass
{
    // AbstractClass interface
public:
    void PrimitiveOperation1();
    void PrimitiveOperation2();
};

#endif // TEMPLATEMETHOD_H
