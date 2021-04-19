#-------------------------------------------------
#
# Project created by QtCreator 2019-02-19T15:20:03
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Design
TEMPLATE = app

SOURCES += \
    main.cpp \
    Design.cpp \
    Strategy/Strategy.cpp \
    Strategy/StrategyClient.cpp \
    CXml.cpp \
    Proxy/Proxy.cpp \
    Proxy/ProxyClient.cpp \
    Prototype/Prototype.cpp \
    Prototype/PrototypeClient.cpp \
    TemplateMethod/TemplateMethod.cpp \
    TemplateMethod/TemplateMethodClient.cpp \
    Facade/FacadeClient.cpp \
    Facade/Facade.cpp \
    Builder/Builder.cpp \
    Builder/BuilderClient.cpp \
    AbstractFactory/AbstractFactory.cpp \
    AbstractFactory/AbstractFactoryClient.cpp \
    State/State.cpp \
    State/StateClient.cpp \
    Adapter/Adapter.cpp \
    Adapter/AdapterClient.cpp \
    Memento/Memento.cpp \
    Memento/MementoClient.cpp \
    Composite/Composite.cpp \
    Composite/CompositeClient.cpp \
    Singleton/Singleton.cpp \
    Singleton/SingletonClient.cpp \
    Bridge/Bridge.cpp \
    Bridge/BridgeClient.cpp \
    Command/Command.cpp \
    Command/CommandClient.cpp \
    Flyweight/Flyweight.cpp \
    Flyweight/FlyweightClient.cpp \
    Interperter/Interperter.cpp \
    Interperter/InterperterClient.cpp \
    Mediator/Mediator.cpp \
    Mediator/MediatorClient.cpp \
    Observer/Observer.cpp \
    Observer/ObserverClient.cpp \
    Responsibility/Responsibility.cpp \
    Responsibility/ResponsibilityClient.cpp \
    Visitor/Visitor.cpp \
    Visitor/VisitorClient.cpp

DLLDESTDIR+= ./lib

DESTDIR+= ./bin

HEADERS += \
    Design.h \
    Strategy/Strategy.h \
    Strategy/StrategyClient.h \
    CXml.h \
    Proxy/Proxy.h \
    Proxy/ProxyClient.h \
    Prototype/Prototype.h \
    Prototype/PrototypeClient.h \
    TemplateMethod/TemplateMethod.h \
    TemplateMethod/TemplateMethodClient.h \
    Facade/FacadeClient.h \
    Facade/Facade.h \
    Builder/Builder.h \
    Builder/BuilderClient.h \
    AbstractFactory/AbstractFactory.h \
    AbstractFactory/AbstractFactoryClient.h \
    State/State.h \
    State/StateClient.h \
    Adapter/Adapter.h \
    Adapter/AdapterClient.h \
    Memento/Memento.h \
    Memento/MementoClient.h \
    Composite/Composite.h \
    Composite/CompositeClient.h \
    Singleton/Singleton.h \
    Singleton/SingletonClient.h \
    Bridge/Bridge.h \
    Bridge/BridgeClient.h \
    Command/Command.h \
    Command/CommandClient.h \
    Flyweight/Flyweight.h \
    Flyweight/FlyweightClient.h \
    Interperter/Interperter.h \
    Interperter/InterperterClient.h \
    Mediator/MediatorClient.h \
    Mediator/Mediator.h \
    Observer/Observer.h \
    Observer/ObserverClient.h \
    Responsibility/Responsibility.h \
    Responsibility/ResponsibilityClient.h \
    Visitor/Visitor.h \
    Visitor/VisitorClient.h
