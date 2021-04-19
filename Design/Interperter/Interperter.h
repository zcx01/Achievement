#ifndef INTERPERTER_H
#define INTERPERTER_H
#include <QObject>
class Context;

//AbstracExpression(抽象表达式),声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享
class AbstracExpression
{
public:
    virtual void interperter(Context *context) = 0;
};

//TerminalExpression(终极符表达式)，实现与文法中的终结符相关联的解释操作。
//实现抽象表达式中所要求的接口，主要是一个interperter()方法。
//文法中每一个终结符都有一个具体终结表达式与之想对应
class TerminalExpression : public AbstracExpression
{
    // AbstracExpression interface
public:
    void interperter(Context *context);
};

//NonterminalExpression(非极符表达式)，为文法中非终结符实现解释操作。
//对文法中每一条规则R1、R2......Rn都需要一个具体的非终结符表达式类。
//通过实现抽象表达式的interperter()方法实现解释操作
//解释器操作以递归方式调用上面提到的代表R1、R2......Rn中各个符号的实例变量
class NonterminalExpression : public AbstracExpression
{
    // AbstracExpression interface
public:
    void interperter(Context *context);
};

//Context，包含解释器之外的一些全局信息
class Context
{
public:
    void setInput(QString text);

    QString getInput();

    void setOutput(QString text);

    QString getOutput();
private:
    QString m_Input;
    QString m_Output;
};

#endif // INTERPERTER_H
