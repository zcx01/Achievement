#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QQmlEngine>
#include "MessageBoard.h"
#include "MessageBody.h"

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ Author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString color READ Color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(MessageBody* body READ Body WRITE setBody NOTIFY bodyChanged)

public:
    static QObject* singleton_provider(QQmlEngine* engine, QJSEngine* scriptEngine)
    {
        Q_UNUSED(scriptEngine);
        Q_UNUSED(engine)
        engine->setObjectOwnership(Instance(),QQmlEngine::CppOwnership);
        return Instance();
    }
    explicit Message(QObject *parent = nullptr);
    explicit Message(const QString &author,const QString &color);
    ~Message();
    static Message*Instance();

    QString Author() const;
    void setAuthor(const QString &Author);

    MessageBody *Body() const;
    void setBody(MessageBody *Body);

    QString Color() const;
    void setColor(const QString &Color);

public slots:
    void cppSlot(QVariant msg);

signals:
    void authorChanged();
    void bodyChanged();
    void colorChanged();

private:

    QString m_Author;
    QString m_Color;
    MessageBody* m_Body;
};

#endif // MESSAGE_H
