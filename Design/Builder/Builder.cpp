#include "Builder.h"
#include <QDebug>

Builder::Builder()
{

}

void Product::Add(QString part)
{
    parts.append(part);
}

void Product::Show()
{
    qDebug()<<"产品 创建";
    foreach (QString part, parts)
    {
        qDebug()<<part;
    }
}


ConcreteBuilder1::ConcreteBuilder1()
{
    m_Product = new Product;
}

void ConcreteBuilder1::BuilderPartA()
{
    m_Product->Add("部件A");
}

void ConcreteBuilder1::BuilderPartB()
{
    m_Product->Add("部件B");
}

Product*  ConcreteBuilder1::GetResult()
{
    return m_Product;
}

ConcreteBuilder2::ConcreteBuilder2()
{
    m_Product = new Product;
}

void ConcreteBuilder2::BuilderPartA()
{
    m_Product->Add("部件X");
}

void ConcreteBuilder2::BuilderPartB()
{
    m_Product->Add("部件Y");
}

Product *ConcreteBuilder2::GetResult()
{
    return m_Product;
}

void Director::Construct(Builder *builder)
{
    builder->BuilderPartA();
    builder->BuilderPartB();
}
