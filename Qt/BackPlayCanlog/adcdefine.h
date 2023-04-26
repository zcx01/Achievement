#ifndef ADCDEFINE_H
#define ADCDEFINE_H

#include <string>

namespace DBC {

struct Message
{
    int id=0;
    std::string sender;
    int lenght=0;

    std::string getMessageId()
    {
//        return std::to_string();
    }
};

struct Sig
{

};

}


#endif // ADCDEFINE_H
