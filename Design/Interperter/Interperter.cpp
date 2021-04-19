#include "Interperter.h"
#include <QDebug>

void TerminalExpression::interperter(Context *context)
{
    qDebug()<<"终极解释器";//要执行的规则
}

void NonterminalExpression::interperter(Context *context)
{
    qDebug()<<"非终极解释器";
}
void Context::setInput(QString text)
{
    m_Input = text;
}

QString Context::getInput()
{
    return m_Input;
}

void Context::setOutput(QString text)
{
    m_Output = text;
}

QString Context::getOutput()
{
    return m_Output;
}
