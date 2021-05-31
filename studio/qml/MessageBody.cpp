#include "MessageBody.h"

MessageBody::MessageBody(QObject *parent):QObject(parent)
{

}

QString MessageBody::Text() const
{
    return m_Text;
}

void MessageBody::setText(const QString &Text)
{
    if(m_Text == Text)return;
    m_Text = Text;
    emit textChanged();
}
