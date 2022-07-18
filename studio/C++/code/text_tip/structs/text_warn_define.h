#ifndef TEXT_WARN_DEFINE_H
#define TEXT_WARN_DEFINE_H

#include <string>
#include <vector>
#include <functional>
#include <base/enum.h>

struct WarnInfo
{
    std::string topic;  
    std::string text;               //文本
    int         grade=0;            //等级
    int         value=0;            //值
    bool        immediately=false;  //立即打断
    int         autoHideTime=0;     //自动隐藏的时间,为-1时不自动取消,0时启用最小显示时间
    int         delay=0;            //延迟显示时间
    bool        immediatelySelf=false;
    //-----------无须赋值
    int         alreadyloopNum=0;   //已经循环的次数
    bool        isNew=true;         //是否新消息
    bool        isCancel=false;     //是否是自动取消
    int         alreadyTime=0;          //已经做过的时间
    bool operator==(const WarnInfo &other)
    {
        return other.topic == topic;
    }

    bool operator < (const WarnInfo & other)
    {
        if(isNew == other.isNew)
        {
            return true;
        }
        return isNew;
    }
};
using  CallWarnInfoFun = std::function<void(const WarnInfo &)>;

BETTER_ENUM(WarnGrade,int,
    W1,
    W2,
    OP1,
    D1,
    D2,
    OP2,
    OP3,
    OP4,
    OP5,
    count
);

enum TimeChangeResult
{
    Finish,
    MinTime,
    Runing
};

namespace Ve
{
    template <typename T>
    bool isBound(const T &ts, int index)
    {
        return index >= 0 && index < (int)ts.size();
    }

    template <typename T,typename U>
    void removeOne(T &ts, const U &value)
    {
        auto iter = std::find(ts.begin(),ts.end(),value);
        if(iter != ts.end())
        {
            ts.erase(iter);
        }
    }

    template <typename T,typename U>
    int count(T &ts, const U &value)
    {
        return std::count(ts.begin(),ts.end(),value);
    }

    template <typename T,typename U>
    int getIndex(T ts, const U &value)
    {
        auto iter = std::find(ts.begin(),ts.end(),value);
        if(iter != ts.end())
        {
           return iter - ts.begin();
        }
        return -1;
    }

    template <typename T>
    void removeFirst(T &ts)
    {
        if(ts.empty()) return;
        ts.erase(ts.begin());
    }

    template <typename T> void move(T &ts,int from, int to)
    {
        if (from == to)
            return;
        if(isBound(ts,from) && isBound(ts,to))
        {
            auto temp = ts[from];
            ts[from] = ts[to];
            ts[to] = temp;
        }
    }

    template <typename T,typename U> U value(T &ts,int index,const U &defaultValue)
    {
        if(isBound(ts,index))
        {
            return ts[index];
        }
        return defaultValue;
    }



}

#endif // TEXT_WARN_DEFINE_H
