#ifndef MESSAGEBODY_H
#define MESSAGEBODY_H
#include <QObject>

class MessageBody : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ Text WRITE setText NOTIFY textChanged)
public:
    MessageBody(QObject* parent=NULL);
    virtual ~MessageBody() {}

    QString Text() const;
    void setText(const QString &Text);

signals:
    void textChanged();

private:
    QString m_Text;
};

#endif // MESSAGEBODY_H
