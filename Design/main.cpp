#include <QApplication>
#include "Design.h"
#include <QDebug>
#include <string>
/**
 *  AbstractFactoryClient:      抽象工厂
 *  AdapterClient:              适配器
 *  BuilderClient:              建造者
 *  CommandClient:              命令
 *  CompositeClient:            组合
 *  FacadeClient:               外观
 *  FlyweightClient:            享元
 *  InterperterClient:          解释器
 *  MediatorClient:             中介者
 *  MementoClient:              备忘录
 *  ObserverClient:             观察者
 *  PrototypeClient:            原型
 *  ProxyClient:                代理
 *  ResponsibilityClient:       职责链
 *  SingletonClient:            单利
 *  StateClient:                状态
 *  StrategyClient:             策略
 *  TemplateMethodClient:       模板方法
 *  VisitorClient:              访问者
 **/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Design::getClient("AdapterClient");
    return a.exec();
}
