#include "test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

TestTest::TestTest(/* args */) 
{
    int a,b;
    printf("1:拳头,2:剪刀,3:布\n");

    printf("请玩家一输入数值:");
    scanf("%d", &a);

    printf("请玩家二输入一个数值:");
    scanf("%d", &b);
    if( (a != 1 && a != 2 && a != 3) || (b != 1 && b != 2 && b != 3) )
    {
        printf("遇到预期之外的错误\n");
        return ;
    }
    if(a == b)
    {
        printf("双方平手");
    }
    else if((a ==1 && b == 2) || (a==2 &&b==1) || (a==3 && b==1))
    {
        printf("玩家一获取胜利");
    }else
    {
        printf("玩家二获取胜利");
    }
    return ;
}

CUSTOMEGISTER(Test,TestTest)