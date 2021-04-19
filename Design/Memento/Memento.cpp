#include "Memento.h"
#include <QDebug>

void Originator::setState(QString state)
{
    m_State = state;
}

QString Originator::getState()
{
    return m_State;
}

Memento *Originator::createMemento()
{
    return new Memento(m_State);
}

void Originator::setMemento(Memento *memento)
{
    if(memento)
        m_State = memento->getState();
}

void Originator::show()
{
    qDebug()<<QString("state ==%1").arg(m_State);
}

Memento::Memento(QString state)
{
    m_State =state;
}

void Memento::setState(QString state)
{
    m_State = state;
}

QString Memento::getState()
{
    return m_State;
}


void Caretaker::setMemento(Memento *memento)
{
    m_Memento = memento;
}

Memento* Caretaker::getMemento()
{
    return m_Memento;
}
