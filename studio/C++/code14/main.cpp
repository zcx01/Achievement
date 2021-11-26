#include <iostream>
#include <type_traits>
#include "ObjectFactory.h"
#include <iostream>
#include "commondefine.hpp"

void exec(std::list<std::string> names,std::string i)
{
     int num = -1;
     try
     {
         num = std::stoi(i) - 1;
     }
     catch (const std::exception &e)
     {
         num = -1;
     }
     int index = 0;
     if (num < names.size() && num >= 0)
     {
         for (auto &name : names)
         {
             if (num == index)
             {
                 ObjectFactory::createObject(name);
                 break;
             }
             index++;
         }
     }
     else
         ObjectFactory::createObject(i);
}

int main(int arg, char *argv[])
{
    std::list<std::string> names;
    ObjectFactory::getObjectName(names);
    const char *ce = "385";
    std::string sc = "385";
    if(std::string(ce) == sc)
    {
        COUT("ddddddd")
    }

#ifdef C385F
    
    COUT("C385")
#endif  // 

#ifdef  C385EV
    COUT("C385EV")
#endif  //C385EV

// #ifndef NDEBUG
//     std::string cl;
//     std::cin >> cl;
//     exec(names, cl);
//     return 0;
// #endif

    if (arg < 2)
    {
        std::cout << "输入参数:" << std::endl;
        std::cout << "-a 表示所有" << std::endl;
        int index = 1;
        for (auto &name : names)
        {
            std::cout << index << "     " << name << std::endl;
            index++;
        }
    }
    else if (std::string(argv[1]) == "-f")
    {
        if (arg < 3)
        {
            std::cout << "输入要查找的内容" << std::endl;
        }
        else
        {
            std::string findContent = argv[2];
            int index = 1;
            for (auto &name : names)
            {
                if (name.find(findContent) != std::string::npos)
                {
                    /* code */
                    std::cout << index << "     " << name << std::endl;
                }
                index++;
            }
        }
    }
    else
    {
        if (std::string(argv[1]) == "-a")
        {
            for (auto &name : names)
            {
                ObjectFactory::createObject(name);
            }
        }
        else
        {
            exec(names, argv[1]);
        }
    }
    return 0;
}
