#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QStack>


//Command类,用来声明执行操作的接口
class Receiver;

class Command
{
public:
    Command(Receiver *receiver);

    virtual void Execute()=0;

protected:
    Receiver *m_Receiver;
};


//将一个接收者对象绑定与一个动作,调用接收者相应的操作，以实现Execute
class ConcreteCommand : public Command
{
    // Command interface
public:
    ConcreteCommand(Receiver *receiver);
    void Execute();
};

//Invoker类，要求该命令执行这个请求
class Invoker
{
public:
    Invoker();
    void setCommand(Command *command);
    void Undo();
    void Redo();

private:
    QStack<Command*> m_Undo;     //撤销
    QStack<Command*> m_Redo;     //重做
};

//Receiver类,知道如何实施与执行一个与请求相关的操作，任何类都可能作为一个接收者
class Receiver
{
public:
    void action();
};

#endif // COMMAND_H
