#ifndef STATE_H
#define STATE_H
#include <QObject>

class State;

//维护一个State子类的实例，这个实例定义的当前的状态
class Context
{
public:
    Context(State* state);

    void setState(State *state);

    State* getState();

    void Request();
private:
    State *m_State;
};

//抽象状态类，定义一个接口以封装与Context的一个特定状态相关实例
class State
{
public:
    virtual void Handle(Context *context)=0;
    virtual QString getName()=0;
};

//具体状态类，每一个子类实现一个与Context的一个状态相关行为
class ConcreteStateA : public State
{

    // State interface
public:
    void Handle(Context *context);
    QString getName();
};

class ConcreteStateB : public State
{

    // State interface
public:
    void Handle(Context *context);
    QString getName();
};
#endif // STATE_H
