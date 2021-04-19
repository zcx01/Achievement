#ifndef PROXY_H
#define PROXY_H

class Subject
{
public:
    virtual void Request() =0;
};

class RealSubject :  public Subject
{

    // Subject interface
public:
    void Request();
};

class Proxy : public Subject
{

public:
    Proxy();
    ~Proxy();

    void Request();

private:

    RealSubject *m_RealSubject;
};

#endif // PROXY_H
