#ifndef TEXTWARNRULE_H
#define TEXTWARNRULE_H

#include <vector>
#include "structs/text_warn_define.h"

class TextWarnRule
{
public:
    virtual ~TextWarnRule(){}
    //显示的最短时间(s)
    virtual int showMinTime();
    
    std::vector<int> Interrupt();

    //得到显示的值
    WarnInfo getValue();

    //得到上一个值
    WarnInfo getPrevValue();
    
    //增加警告信息
    bool addWarnInfo(const WarnInfo &info);
    
    //移除第一个
    void removeFirst();

    //第一个移动最后一个
    void move();

    //时间改变
    TimeChangeResult changed();

    //增加时间
    void addTime();

    //有新的警告
    bool isNewWarn(int index=0);

    bool isEmpty();

    //等级
    virtual int grade() = 0;
protected:
    //自动隐藏的时间(s)
    virtual int autoHideTime();

    virtual bool newWarnInfo();
    virtual TimeChangeResult timeChange()=0;

    int                     alreadyTime=0;//已经显示的时间
    std::vector<WarnInfo>   warns;        //要显示警告信息
    std::vector<int>        m_Interrupts;
    WarnInfo                m_PrevValue;  //上一个值
};


class LoopTextWarnRule : public TextWarnRule
{
public:
    using TextWarnRule::TextWarnRule;

protected:
    bool newWarnInfo();
    TimeChangeResult timeChange();

};

class TimeLoopTextWarnRule : public TextWarnRule
{
public:
    using TextWarnRule::TextWarnRule;

protected:
    bool newWarnInfo();
    TimeChangeResult timeChange();
};

//单次
class SingleTextWarnRule  : public TextWarnRule
{
private:
    /* data */
public:
    using TextWarnRule::TextWarnRule;
protected:
    TimeChangeResult timeChange();
    int showMinTime();
};

//保留最后一个
class LastTextWarnRule  : public TextWarnRule
{
private:
    /* data */
public:
    using TextWarnRule::TextWarnRule;
protected:
    TimeChangeResult timeChange();
};

#endif // TEXTWARNRULE_H
