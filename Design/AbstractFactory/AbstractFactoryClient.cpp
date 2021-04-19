#include "AbstractFactoryClient.h"
#include "AbstractFactory.h"

AbstractFactoryClient::AbstractFactoryClient()
{
}

AbstractFactoryClient::~AbstractFactoryClient()
{

}


void AbstractFactoryClient::Test()
{
    User *user = new User;
    Department *dept = new Department;

    IUser *iu = DataAccess::createUser("SqlserverUser");

    iu->Insert(user);
    iu->getUser(1);

    IDepartment *id = DataAccess::createDepartment("SqlserverDepartment");
    id->Insert(dept);
    id->GetDepartment(1);
}
MYREGISTER(AbstractFactoryClient)
