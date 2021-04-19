#ifndef MEMENTO_H
#define MEMENTO_H
#include <QObject>

class Memento;

//发起人:负责创建一个备忘录Memento,用以记录当前时刻它的内部状态，并可使用备忘录恢复
//内部状态。可以根据需要决定Memento储存Originator的哪些状态
class Originator
{
public:
    void setState(QString state);

    QString getState();

    Memento* createMemento();

    void setMemento(Memento *memento);

    void show();
private:
    QString m_State;
};

//备忘录类:负责储存Originator对象的内部状态，并可防止Originator以外的其他对象访问备忘录Memento
//备忘录有两个接口，Caretaker只能看见备忘录的窄接口，它只能将备忘录传递给其他对象，
//Originator能够看到一个宽接口,允许它访问返回到先前状态所需的所有数据
class Memento
{
public:
    Memento(QString state);

    void setState(QString state);

    QString getState();

private:
    QString m_State;
};


//管理者类:负责保存好备忘录Memento,不能对备忘录的内容操作或者数据
class Caretaker
{
public:
    void setMemento(Memento *memento);

    Memento* getMemento();
private:
    Memento *m_Memento;
};

#endif // MEMENTO_H
