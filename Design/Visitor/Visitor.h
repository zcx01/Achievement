#ifndef VISITOR_H
#define VISITOR_H
#include <QObject>

//Visitor类，为该对象结构中ConcreteElement的每一个类声明一个Visitor操作
class ConcreteElementA;
class ConcreteElementB;
class Visitor
{
public:
    virtual void VisitorConcreteElementA(ConcreteElementA *concreteElementA) =0;
    virtual void VisitorConcreteElementB(ConcreteElementB *concreteElementB) =0;
};

//ConcreteVisitor1和ConcreteVisitor2类，具体访问者，实现每个有Visitor声明的操作
//每一个操作实现算法的一部分，而该算法片段乃是对应与结构体中对象的类
class ConcreteVisitor1 : public Visitor
{
    // Visitor interface
public:
    void VisitorConcreteElementA(ConcreteElementA *concreteElementA);
    void VisitorConcreteElementB(ConcreteElementB *concreteElementB);
};

class ConcreteVisitor2 : public Visitor
{
    // Visitor interface
public:
    void VisitorConcreteElementA(ConcreteElementA *concreteElementA);
    void VisitorConcreteElementB(ConcreteElementB *concreteElementB);
};

//Element类，定义一个Accpet操作，它一个访问者为参数
class Element
{
public:
    virtual void Accpet(Visitor *visitor) =0;
    virtual QString getName() =0;
};

//ConcreteElementA和ConcreteElementB,具体元素，实现Accpet操作
class ConcreteElementA : public Element
{
    // Element interface
public:
    void Accpet(Visitor *visitor);
    QString getName();
    void OprationA();//其他方法操作
};

class ConcreteElementB : public Element
{
    // Element interface
public:
    void Accpet(Visitor *visitor);
    QString getName();
    void OprationB();//其他方法操作
};

class ObjectStruct
{
public:
    void Attch(Element *element);
    void Detach(Element *element);
    void Accept(Visitor *visitor);

private:
    QList<Element*> m_Elements;
};

#endif // VISITOR_H
