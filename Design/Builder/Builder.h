#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>

class Product
{
public:
    void Add(QString part);

    void Show();

private:
    QList<QString> parts;
};

class Builder
{
public:
    Builder();
    virtual void  BuilderPartA() =0;
    virtual void  BuilderPartB() =0;
    virtual Product*  GetResult() =0;
};

class ConcreteBuilder1 : public Builder
{
public:
    ConcreteBuilder1();

    void BuilderPartA();
    void BuilderPartB();
    Product*  GetResult();

private:
    Product *m_Product;
};

class ConcreteBuilder2 : public Builder
{
public:
    ConcreteBuilder2();

    void BuilderPartA();
    void BuilderPartB();
    Product*  GetResult();

private:
    Product *m_Product;
};

class Director
{
public:
    void Construct(Builder *builder);
};

#endif // BUILDER_H
