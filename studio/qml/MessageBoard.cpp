#include "MessageBoard.h"

MessageBoardAttachedType::MessageBoardAttachedType(QObject *obj) : QObject(obj)
{

}

QString MessageBoardAttachedType::Expried() const
{
    return m_Expried;
}

void MessageBoardAttachedType::setExpried(const QString &Expried)
{
    if(m_Expried != Expried){
        m_Expried = Expried;
        emit expriedChanged();
    }
}

MessageBoardAttachedType *MessageBoard::qmlAttachedProperties(QObject *obj)
{
    return new MessageBoardAttachedType(obj);
}
