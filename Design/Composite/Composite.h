#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <QObject>

//为组合中的对象声明一个接口，在适当的情况下，实现所有类的共有接口的默认行为。
//声明一个接口用于访问和管理Compositedd的子对象
class Component
{
public:
    explicit Component(QString name);

    virtual void add(Component *c) =0;

    virtual void remove(Component *c) =0;

    virtual void Display(int depth);

protected:
    QString m_Name;
};

//叶子节点对象,实现接口，让它们具备完全一致的接口
class Leaf : public Component
{

    // Composite interface
public:
    Leaf(QString name) : Component(name){}

    void add(Component *c);

    void remove(Component *c);
};

//定义了枝节点行为,用于储存子部件，在Component接口中实现与子部件相关的操作
class Composite : public Component
{
    // Component interface
public:
    Composite(QString name) : Component(name){}
    void add(Component *c);
    void remove(Component *c);
    void Display(int depth);

private:
    QList<Component*> m_Children;
};

#endif // COMPOSITE_H
