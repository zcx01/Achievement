#include "template_using.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include <vector>

template<typename T,typename U> class MagicType{
public:
    T dark;
    U magic;
};

template<typename T> using TrueDarkMagic = MagicType<std::vector<T>,std::string>;
typedef int (*process)(void *);
using NewProcess=int(*)(void *);

TemplateUsingTest::TemplateUsingTest(/* args */) 
{
    TrueDarkMagic<bool> you;
}

CUSTOMEGISTER(TemplateUsing,TemplateUsingTest)