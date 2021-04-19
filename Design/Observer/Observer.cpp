#include "Observer.h"
#include <QDebug>

Observer::Observer()
{

}

void Subject::Attach(Observer *observer)
{
    m_Observers.append(observer);
}

void Subject::Detach(Observer *observer)
{
    m_Observers.removeOne(observer);
}

void Subject::Notify()
{
    foreach (Observer *ob, m_Observers)
    {
        ob->Update();
    }
}

void ConcreteSubject::setSubjectState(QString str)
{
    m_SubjectState =str;
}

QString ConcreteSubject::getSubjectState()
{
    return m_SubjectState;
}

ConcreteObserver::ConcreteObserver(ConcreteSubject *subject, QString name)
{
    m_ConcreteSubject = subject;
    m_Name = name;
}

void ConcreteObserver::Update()
{
    m_ObserverState = m_ConcreteSubject->getSubjectState();
    qDebug()<<QString("观察者%1的新状态是%2").arg(m_Name).arg(m_ObserverState);
}
