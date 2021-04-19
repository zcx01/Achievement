#ifndef RESPONSIBILITY_H
#define RESPONSIBILITY_H

//定义一个处理请示接口
class Handler
{
public:
    Handler();
    void setSuccessor(Handler *successor);

    virtual void HandlerRequest(int request) =0;
protected:
    Handler* m_Successor;
};

//ConcreteHandler类，具体处理者类，处理它所负责的请求，
//可访问它的后继者，如果可处理该请求就处理
//否则就将该请求转发给它的后继者


//ConcreteHandler1，当请求数扎起0到10之间则有权限处理，负责转给下一位
class ConcreteHandler1 :public Handler
{
public:
    void HandlerRequest(int request);
};

//ConcreteHandle2，当请求数扎起10到20之间则有权限处理，负责转给下一位
class ConcreteHandler2 :public Handler
{
public:
    void HandlerRequest(int request);
};

//ConcreteHandler3，当请求数扎起20到30之间则有权限处理，负责转给下一位
class ConcreteHandler3 :public Handler
{
public:
    void HandlerRequest(int request);
};

#endif // RESPONSIBILITY_H
