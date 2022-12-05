#include "ctest.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

//scanf 使用后在使用 getchar 获取字符，有先用 getchar 清空一下字符
//scanf("%s",chars);
ctestTest::ctestTest(/* args */) 
{
    printf("请输入一个字符串:");
    char str[1024]; 
    int intPutSize = 0;
    char c;
    while ( (c = getchar()) != '\n')
    {
        str[intPutSize] = c;
        intPutSize++;
    }

    printf("请输入一个字符:");
    c = getchar();
    int isFind = 0;
    for (int i = 0; i < intPutSize; i++)
    {
        if (str[i] == c)
        {
            printf("%d \n", i);
            isFind = 1;
        }
    }
    if (isFind == 0)
        printf("%d\n", -1);
}

CUSTOMEGISTER(ctest,ctestTest)