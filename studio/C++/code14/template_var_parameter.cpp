#include "template_var_parameter.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include <initializer_list>
#include <functional>
#include "commondefine.hpp"

#if __cplusplus > 201402L
//C++ 17
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}
#endif

using downSigChange = std::function<void(const std::string&,const float &)>;
#define BINGDOWNSIGCHANGE(v,W) std::bind(v,W,std::placeholders::_1,std::placeholders::_2)
static std::unordered_map<std::string,downSigChange> downSigChanges;
void callTopicChanged(const std::string & topic,const float &value)
{
    auto fun = downSigChanges[topic];
    if(fun == nullptr)
    {
        return;
    }
    fun(topic,value);
}
void registerSigChangeFun(const std::string & topic,downSigChange fun);
template <typename ... T> void DummyWrapper(T... t){};
template <class T>
T unpacker(downSigChange fun,const T& t){
    downSigChanges[t] = fun;
    COUT(t)
    return t;
}

template<typename... Ts> 
void registerSigChangeFun2(downSigChange fun,Ts... args){
    DummyWrapper(fun,unpacker(fun,args)...);
}

void D(const std::string&t,const float &d)
{
    COUT(t<<"   "<<d);
}

TemplateVarParameterTest::TemplateVarParameterTest(/* args */) 
{
    registerSigChangeFun2(std::bind(&D,std::placeholders::_1,std::placeholders::_2),"dddss","dsssss");
    callTopicChanged("dddss",12);
}

CUSTOMEGISTER(TemplateVarParameter,TemplateVarParameterTest)