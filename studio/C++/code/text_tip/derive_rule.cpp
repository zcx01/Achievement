#include "derive_rule.hpp"
#include <algorithm>


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