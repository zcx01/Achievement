#include "text_warn_rule.hpp"
#include <algorithm>

int TextWarnRule::showMinTime()
{
    return 2;
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

int TextWarnRule::removeWarnInfo(const WarnInfo &info)
{
    int infoIndex = Ve::getIndex(warns, info);
    if(infoIndex == -1) return -1;
    Ve::removeOne(warns, info);
    return grade();
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
        warns[0].alreadyloopNum++;
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
        WarnInfo &info = warns[0];
        //延迟显示，时间不累计
        if (info.delay > 0)
        {
            info.delay--;
            return TimeChangeResult::Runing;
        }
        
        alreadyTime++;
        info.alreadyTime = alreadyTime;
        if(info.isCancel && alreadyTime >= showMinTime())
        {
            removeFirst();
            return TimeChangeResult::MinTime;
        }
        else
        {
            auto reslut = timeChange();
            alreadyTime = std::min(alreadyTime,std::max(autoHideTime(),showMinTime()));
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

int TextWarnRule::TextWarnRule::getAlreadyTime() 
{
    return alreadyTime;    
}

//-------------------------------------
bool TimeLoopTextWarnRule::newWarnInfo()
{
    if(alreadyTime > showMinTime())
    {
        move();
        return true;
    }
    return false;
}

TimeChangeResult TimeLoopTextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        if (!isEmpty())
        {
            WarnInfo info = getValue();
            if(info.alreadyloopNum >= autoHideTime() / 2)
            {
                removeFirst();
            }
            else
            {
                move();
            }
        }
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}

//-------------------------------------
bool LoopTextWarnRule::newWarnInfo()
{
    if(alreadyTime > showMinTime())
    {
        move();
        return true;
    }
    return false;
}

TimeChangeResult LoopTextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        move();
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}

//-------------------------------------
TimeChangeResult SingleTextWarnRule::timeChange()
{
    if(autoHideTime() != showMinTime())
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
    }
    else
    {
        if(alreadyTime >= showMinTime())
        {
            removeFirst();
            return TimeChangeResult::MinTime;
        }
    }
    return TimeChangeResult::Runing;
}

int SingleTextWarnRule::autoHideTime() 
{
    return 3;    
}

//---------------------------------------
TimeChangeResult LastTextWarnRule::timeChange()
{
    if(alreadyTime >= showMinTime())
    {
        if(warns.size() > 1)
            removeFirst();
        return TimeChangeResult::MinTime;
    }
    return TimeChangeResult::Runing;
}

