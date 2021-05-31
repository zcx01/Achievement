#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>
#include "Message.h"
#include "MyWidget.h"
#include <QQmlComponent>
#include <QQmlProperty>
#include <QQuickItem>
#include "calenum.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    CalEnum cal;

    qmlRegisterType<MessageBoard>("TEST.messging",1,0,"MessageBoard");
    qmlRegisterType<Message>("TEST.messging",1,0,"Message");
    qmlRegisterType<MessageBody>("TEST.messging",1,0,"MessageBody");
    qmlRegisterType<CalEnum>("TEST.messging",1,0,"CalEnum");
    qmlRegisterSingletonType<Message>("TEST.messging",1,0,"Message",&Message::singleton_provider);
    qmlRegisterSingletonType(QUrl("qrc:/MySingleton.qml"),"qml.Singleton",1,0,"MySingleton");


    QQmlApplicationEngine engine;
    QQmlContext * content = engine.rootContext();
    QStringListModel strings;
    strings.setStringList(QStringList()<<"item1"<<"item2"<<"item3");
    content->setContextProperty("stringModel",&strings);

//    Message msg;
//    content->setContextProperty("msg",&msg);

//    QObjectList objectList;
//    objectList.append(new Message("Item 1","red"));
//    objectList.append(new Message("Item 1","green"));
//    objectList.append(new Message("Item 1","blue"));
//    content->setContextProperty("objectListModel",QVariant::fromValue(objectList));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    QQmlEngine e;
//    QQmlComponent comonent(&e,QUrl(QStringLiteral("qrc:/main.qml")));
//    QObject* object = comonent.create();

    QObject* object  = engine.rootObjects().value(0);


//    QObject::connect(object,SIGNAL(qmlSignal(QVariant)),&msg,SLOT(cppSlot(QVariant)));

    return app.exec();
}
