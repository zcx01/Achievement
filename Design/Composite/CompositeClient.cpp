#include "CompositeClient.h"
#include "Composite.h"

CompositeClient::CompositeClient()
{
}

CompositeClient::~CompositeClient()
{

}


void CompositeClient::Test()
{
    Composite root("root");
    root.add(new Leaf("Leaf A"));
    root.add(new Leaf("Leaf B"));

    Composite comp("Compsoite X");
    comp.add(new Leaf("Leaf XA"));
    comp.add(new Leaf("Leaf XB"));

    root.add(&comp);

    Composite comp2("Compsoite XY");
    comp2.add(new Leaf("Leaf XYA"));
    comp2.add(new Leaf("Leaf XYB"));

    comp.add(&comp2);

    root.add(new Leaf("Leaf c"));

    Leaf leaf("Leaf D");
    root.add(&leaf);
    root.remove(&leaf);

    root.Display(0);
}

MYREGISTER(CompositeClient)
