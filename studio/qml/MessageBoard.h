#ifndef MessageBoard_H
#define MessageBoard_H
#include <QObject>
#include <QQmlEngine>

class MessageBoardAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString expried READ Expried WRITE setExpried NOTIFY expriedChanged)
public:
    MessageBoardAttachedType(QObject *obj=NULL);
    virtual ~MessageBoardAttachedType() {}

    QString Expried() const;
    void setExpried(const QString &Expried);

signals:
    void expriedChanged();

private:
    QString m_Expried;
};

class MessageBoard : public QObject
{
    Q_OBJECT
public:
    static MessageBoardAttachedType* qmlAttachedProperties(QObject* obj);
};
QML_DECLARE_TYPEINFO(MessageBoard,QML_HAS_ATTACHED_PROPERTIES)
#endif // MessageBoardAttachedType_H
