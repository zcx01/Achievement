#ifndef FACADE_H
#define FACADE_H

class SubSystemOne
{
public:
    void MethodOne();
};

class SubSystemTwo
{
public:
    void MethodTwo();
};

class SubSystemThree
{
public:
    void MethodThree();
};

class SubSystemFour
{
public:
    void MethodFour();
};


//外观类，它需要了解所有的子系统的方法或者属性，进行组合，以备外界调用
class Facade
{
public:
    Facade();
    ~Facade();

    void MethodA();

    void MethodB();

private:
    SubSystemOne*       m_SubSystemOne;
    SubSystemTwo*       m_SubSystemTwo;
    SubSystemThree*     m_SubSystemThree;
    SubSystemFour*      m_SubSystemFour;
};

#endif // FACADE_H
