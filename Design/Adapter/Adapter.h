#ifndef ADAPTER_H
#define ADAPTER_H

//客户所期待的接口
class Target
{
public:
    virtual void Request();
};

//需要适配的类
class Adaptee
{
public:
    void SpecificRequest();
};

//适配器类，把源接口转化成目标接口
class Adapter :public Target
{
public:
    Adapter();
    ~Adapter();

    // Target interface
public:
    void Request();

private:
    Adaptee *m_Adaptee;
};

#endif // ADAPTER_H
