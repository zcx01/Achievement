#include <iostream>
#include <type_traits>
#include "ObjectFactory.h"
#include <iostream>

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

    // int a,b;
    // printf("1:拳头,2:剪刀,3:布");

    // printf("请玩家一输入数值");
    // scanf("%d", &a);

    // printf("请玩家二输入一个数值");
    // scanf("%d", &b);
    // if(a == b)
    // {
    //     printf("双方平手");
    // }
    // else if((a ==1 && b == 2) || (a==2 &&b==1) || (a==3 && b==1))
    // {
    //     printf("玩家一获取胜利");
    // }else
    // {
    //      printf("玩家二获取胜利");
    // }
    // printf("遇到预期之外的错误\n");

    return 0;
}
