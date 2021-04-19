#include "MementoClient.h"
#include "Memento.h"

MementoClient::MementoClient()
{
}

MementoClient::~MementoClient()
{

}

void MementoClient::Test()
{
    Originator o;
    o.setState("On");
    o.show();

    Caretaker c;
    c.setMemento(o.createMemento());

    o.setState("Off");
    o.show();

    o.setMemento(c.getMemento());
    o.show();
}
MYREGISTER(MementoClient)
