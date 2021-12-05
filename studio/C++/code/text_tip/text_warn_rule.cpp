#include "text_warn_rule.hpp"
#include <algorithm>

int TextWarnRule::showMinTime()
{
    return 3;
}

std::vector<int> TextWarnRule::Interrupt()
{
    return m_Interrupts;
}

WarnInfo TextWarnRule::getValue()
{
    if(warns.empty()) return WarnInfo();
    return warns[0];
}

WarnInfo TextWarnRule::TextWarnRule::getPrevValue() 
{
    return m_PrevValue;
}

bool TextWarnRule::addWarnInfo(const WarnInfo &info)
{
    newWarnInfo();
    //取消显示 text 是空的取消显示
    int infoIndex = Ve::getIndex(warns, info);
    if(info.text.empty())
    {
        if(infoIndex!= -1)
        {
            warns[infoIndex].isCancel = true;
        }
        return false;
    }
    else
    {
        if(infoIndex!= -1)
        {
            warns[infoIndex] = info;
        }
        else
        {
            //把新的消息放在其他新消息后面
            Ve::removeOne(warns, info);
            auto index = 0;
            for (auto w : warns)
            {
                if (w.isNew == false)
                {
                    break;
                }
                index++;
            }
            warns.insert(warns.begin() + index, info);
        }
        return true;
    }
    return false;
}

void TextWarnRule::removeFirst()
{
    if(!warns.empty())
    {
        m_PrevValue= warns[0];
        Ve::removeFirst(warns);
        alreadyTime=0;
    }
}

void TextWarnRule::move()
{
    if(!warns.empty())
    {
        warns[0].isNew = false;
        Ve::move(warns,0,warns.size()-1);
        alreadyTime=0;
    }
}

TimeChangeResult TextWarnRule::changed()
{
    if(warns.empty())
    {
        return TimeChangeResult::Finish;
    }
    else
    {
        alreadyTime++;
        WarnInfo info = warns[0];
        if(info.isCancel && alreadyTime >= showMinTime())
        {
            removeFirst();
            return TimeChangeResult::MinTime;
        }
        else
        {
            auto reslut = timeChange();
            alreadyTime = std::min(alreadyTime, autoHideTime());
            return reslut;
        }
    }
}

void TextWarnRule::addTime()
{
    alreadyTime++;
}

bool TextWarnRule::isNewWarn(int index)
{
    if(!Ve::isBound(warns,index))
    {
        return false;
    }
    return warns[index].isNew;
}

bool TextWarnRule::isEmpty()
{
    return warns.empty();
}

int TextWarnRule::autoHideTime()
{
    if(!isEmpty())
    {
        auto info = getValue();
        if(info.autoHideTime != 0)
        {
            return info.autoHideTime;
        }
    }
    return showMinTime();
}

bool TextWarnRule::newWarnInfo()
{
    if(alreadyTime >= showMinTime())
    {
        removeFirst();
        return true;
    }
    return false;
}


///
/// \brief CTextWarnRule::CTextWarnRule
///
CTextWarnRule::CTextWarnRule()
{
    m_Interrupts.push_back(WarnGrade::B1);
    m_Interrupts.push_back(WarnGrade::B2);
    m_Interrupts.push_back(WarnGrade::C);
}

int CTextWarnRule::autoHideTime()
{
    return 5;
}

int CTextWarnRule::grade()
{
    return WarnGrade::C;
}

TimeChangeResult CTextWarnRule::timeChange()
{
    if(alreadyTime >= autoHideTime())
    {
        removeFirst();
        return TimeChangeResult::Finish;
    }
    else if(alreadyTime >= showMinTime())
    {
        if(isNewWarn(1))
        {
            removeFirst();
        }
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}


///
/// \brief B2TextWarnRule::B2TextWarnRule
///
B2TextWarnRule::B2TextWarnRule()
{
    m_Interrupts.push_back(WarnGrade::B2);
    m_Interrupts.push_back(WarnGrade::A);
    m_Interrupts.push_back(WarnGrade::C);
    m_Interrupts.push_back(WarnGrade::D);
}

int B2TextWarnRule::autoHideTime()
{
    return 3;
}

int B2TextWarnRule::grade()
{
    return WarnGrade::B2;
}

bool B2TextWarnRule::newWarnInfo()
{
    if(alreadyTime > showMinTime())
    {
        move();
        return true;
    }
    return false;
}

TimeChangeResult B2TextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        move();
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}

///
/// \brief B1TextWarnRule::grade
/// \return
///
B1TextWarnRule::B1TextWarnRule()
{
    m_Interrupts.push_back(WarnGrade::B1);
    m_Interrupts.push_back(WarnGrade::A);
    m_Interrupts.push_back(WarnGrade::C);
    m_Interrupts.push_back(WarnGrade::D);
}

int B1TextWarnRule::grade()
{
    return WarnGrade::B1;
}

int B1TextWarnRule::autoHideTime()
{
    return 3;
}

TimeChangeResult B1TextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        removeFirst();
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}

///
/// \brief ATextWarnRule::ATextWarnRule
///
ATextWarnRule::ATextWarnRule()
{

}

int ATextWarnRule::grade()
{
    return WarnGrade::A;
}

int ATextWarnRule::autoHideTime()
{
    return 3;
}

TimeChangeResult ATextWarnRule::timeChange()
{
    if(alreadyTime > showMinTime())
    {
        removeFirst();
        return TimeChangeResult::Finish;
    }
    return TimeChangeResult::Runing;
}

///
/// \brief DTextWarnRule::grade
/// \return
///
DTextWarnRule::DTextWarnRule()
{
    m_Interrupts.push_back(WarnGrade::D);
}

int DTextWarnRule::grade()
{
    return WarnGrade::D;
}

int DTextWarnRule::autoHideTime()
{
    return 3;
}

TimeChangeResult DTextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        if(warns.size() > 1)
            removeFirst();
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}