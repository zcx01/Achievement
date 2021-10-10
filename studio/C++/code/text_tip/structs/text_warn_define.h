#ifndef TEXT_WARN_DEFINE_H
#define TEXT_WARN_DEFINE_H

#include <string>
#include <vector>
#include <functional>
struct WarnInfo
{
    std::string topic;
    std::string value;
    int         grade=0;
    int         key=0;
    bool    isNew=true;
    bool    isCancel=false;
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

enum WarnGrade
{
    C,
    B2,
    B1,
    A,
    D,
    count
};

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
