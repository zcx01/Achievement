#include "Command.h"
#include <QDebug>

Command::Command(Receiver *receiver)
{
    m_Receiver = receiver;
}

ConcreteCommand::ConcreteCommand(Receiver *receiver) :Command(receiver)
{

}

void ConcreteCommand::Execute()
{
    m_Receiver->action();
}
Invoker::Invoker()
{
}

void Invoker::setCommand(Command *command)
{
    command->Execute();
    //保存当前命令
    m_Undo.push(command);
}

void Invoker::Undo()
{
    if(m_Undo.size() < 2)
    {
        qDebug() << "Undo failed";
        return;
    }

    //当前命令
    Command* pCmd = m_Undo.top();

    //保存当前命令
    m_Redo.push(pCmd);

    //弹出
    m_Undo.pop();

    //还原上个命令
    pCmd = m_Undo.top();

    pCmd->Execute();
}

void Invoker::Redo()
{
    if(m_Redo.empty())
    {
        qDebug() << "Redo failed";
        return;
    }
    Command* pCmd =  m_Redo.top();

    pCmd->Execute();

    //还原上个命令
    m_Redo.pop();

    m_Undo.push(pCmd);
}


void Receiver::action()
{
    qDebug()<<"执行请求!";
}
