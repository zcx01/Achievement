#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>

//抽象观察者
class Observer
{
public:
    Observer();
    virtual void Update() =0;
};

//主题或抽象通知者
class Subject
{
public:
    //添加观察者
    void Attach(Observer *observer);

    //移除观察者
    void Detach(Observer *observer);

    //通知
    void Notify();

private:
    QList<Observer*> m_Observers;
};

//具体主题或通知者，将有关状态存入具体观察者对象，在具体主题的内部状态改变时，
//给使用登记过的观察者发出通知
class ConcreteSubject : public Subject
{
public:
    void setSubjectState(QString str);

    QString getSubjectState();
private:
    QString m_SubjectState;
};

//具体观察者，实现抽象观察者角色所要求的跟新接口，以便是本身的状态与主题一致
//具体观察者角色可以保存一个指向具体主题对象的引用
class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(ConcreteSubject *subject,QString name);

    void Update();
private:
    QString             m_Name;
    QString             m_ObserverState;
    ConcreteSubject*    m_ConcreteSubject;
};

#endif // OBSERVER_H
