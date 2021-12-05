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
    
    //等级
    virtual int grade() = 0;
    
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

class CTextWarnRule : public TextWarnRule
{
    // TextWarnRule interface
public:
    CTextWarnRule();
    int autoHideTime();
    int grade();
    TimeChangeResult timeChange();
};

class B2TextWarnRule : public TextWarnRule
{
    // TextWarnRule interface
public:
    B2TextWarnRule();
    int autoHideTime();
    int grade();
    bool newWarnInfo();
    TimeChangeResult timeChange();
};

class B1TextWarnRule : public TextWarnRule
{

    // TextWarnRule interface
public:
    B1TextWarnRule();
    int grade();

protected:
    int autoHideTime();
    TimeChangeResult timeChange();
};

class ATextWarnRule : public TextWarnRule
{
    // TextWarnRule interface
public:
    ATextWarnRule();
    int grade();

protected:
    int autoHideTime();
    TimeChangeResult timeChange();
};

class DTextWarnRule : public TextWarnRule
{

    // TextWarnRule interface
public:
    DTextWarnRule();
    int grade();

protected:
    int autoHideTime();
    TimeChangeResult timeChange();
};

#endif // TEXTWARNRULE_H
