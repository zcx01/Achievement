#include "Message.h"
#include <QDebug>

Message::Message(QObject *parent) : QObject(parent)
{
    m_Body=NULL;
}

Message::Message(const QString &author, const QString &color)
{
    m_Body = NULL;
    m_Author = author;
    m_Color = color;
}

Message::~Message()
{
    qDebug()<<Author()<<"~Message";
}

Message *Message::Instance()
{
    static Message instance;
    return &instance;
}

QString Message::Author() const
{
    return m_Author;
}

void Message::setAuthor(const QString &Author)
{
    if(Author != m_Author){
        m_Author = Author;
        emit authorChanged();
    }
}

MessageBody *Message::Body() const
{
    return m_Body;
}

void Message::setBody(MessageBody *Body)
{
    if(m_Body == Body) return;
    m_Body = Body;
    emit bodyChanged();
}

void Message::cppSlot(QVariant msg)
{
    QObject* obj = msg.value<QObject*>();
    qDebug()<<obj->property("width");
}

QString Message::Color() const
{
    return m_Color;
}

void Message::setColor(const QString &Color)
{
    if(m_Color == Color) return;
    m_Color = Color;
    emit colorChanged();
}

