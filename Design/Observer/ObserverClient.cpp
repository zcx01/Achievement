#include "ObserverClient.h"
#include "Observer.h"

ObserverClient::ObserverClient()
{
}

ObserverClient::~ObserverClient()
{

}

void ObserverClient::Test()
{
    ConcreteSubject s;
    s.Attach(new ConcreteObserver(&s,"X"));
    s.Attach(new ConcreteObserver(&s,"Y"));
    s.Attach(new ConcreteObserver(&s,"Z"));

    s.setSubjectState("ABC");
    s.Notify();
}
MYREGISTER(ObserverClient)
