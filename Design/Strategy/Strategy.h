#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
class Strategy
{
public:
    Strategy();
    virtual ~Strategy();

    virtual void AlgorithmInterface()=0;
};

class ConcreteStrategyA : public Strategy
{
    // Strategy interface
public:
    void AlgorithmInterface();
};

class ConcreteStrategyB : public Strategy
{
    // Strategy interface
public:
    void AlgorithmInterface();
};

class ConcreteStrategyC : public Strategy
{
    // Strategy interface
public:
    void AlgorithmInterface();
};

class Context
{
public:
    Context(Strategy *strategy);
    ~Context();

    //根据具体的策略对象，调用其算法的方法
    void ContextInterface();
private:

    Strategy *m_Strategy;
};

class StrategyObject
{
public:
    static Context *creatorObject(QByteArray className);
};
#endif // STRATEGY_H
