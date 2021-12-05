#include "text_warn_rule_manage.hpp"
#include "text_warn_rule.hpp"
#include <algorithm>

TextWarnRuleManage::TextWarnRuleManage()
{
    std::vector<std::string> gradeStr;
    gradeStr.push_back("C");
    gradeStr.push_back("B2");
    gradeStr.push_back("B1");
    gradeStr.push_back("A");
    gradeStr.push_back("D");
    for(int i = WarnGrade::count-1; i >= WarnGrade::C;i--)
    {
        m_warnRule.push_back(createRule(i));
        m_GradeStr[Ve::value(gradeStr,i,std::string(""))]=WarnGrade::count-i-1;
    }
}

TextWarnRuleManage::~TextWarnRuleManage()
{
    for(auto iter = m_warnRule.begin();iter != m_warnRule.end();iter++)
    {
        delete *iter;
    }
}

bool TextWarnRuleManage::addWarnInfo(const std::string &grade,WarnInfo &info)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_GradeStr.count(grade) == 0) return false;
    int index = m_GradeStr[grade];
    if(!Ve::isBound(m_warnRule,index)) return false;
    auto rule = m_warnRule[index];
    
    if(rule != nullptr)
    {
        info.grade=rule->grade();
        bool status=rule->addWarnInfo(info);
        if(status && m_currentRule == nullptr)
        {
            setCurrentRule(rule);
        }
        return status;
    }
    return false;
}

void TextWarnRuleManage::timeOut()
{
    if(m_currentRule != nullptr)
    {
        TimeChangeResult result = m_currentRule->changed();
        //打断rule
        if(result == TimeChangeResult::MinTime)
        {
            std::vector<int> interrupt = m_currentRule->Interrupt();
            std::sort(interrupt.begin(),interrupt.end(),[](const int &f,const int &t){return  t < f;});
            std::vector<TextWarnRule*> rules;
            for(auto inter : interrupt)
            {
                rules.push_back(getRuleByGrade(inter));
            }
            for(auto rule: rules)
            {
                if(rule != nullptr && rule->isNewWarn() && !rule->isEmpty())
                {
                    setCurrentRule(rule);
                    return;
                }
            }
        }
        else if(result == TimeChangeResult::Runing)
        {
            return;
        }
        else if(result == TimeChangeResult::Finish)
        {

        }
    }

    for(auto rule : m_warnRule)
    {
        if(rule != nullptr && !rule->isEmpty())
        {
            if(m_currentRule == nullptr)
            {
                rule->changed();
            }
            setCurrentRule(rule);
            return;
        }
    }
    setCurrentRule(nullptr);
}

TextWarnRule *TextWarnRuleManage::createRule(const int &grade)
{
    switch (grade)
    {
    case WarnGrade::C:
        return new CTextWarnRule;
    case WarnGrade::B2:
        return new B2TextWarnRule;
    case WarnGrade::B1:
        return new B1TextWarnRule;
    case WarnGrade::A:
        return new ATextWarnRule;
    case WarnGrade::D:
        return new DTextWarnRule;
    }
    return nullptr;
}

TextWarnRule *TextWarnRuleManage::getRuleByGrade(const int &grade)
{
    for(auto rule : m_warnRule)
    {
        if(rule->grade() == grade)
        {
            return rule;
        }
    }
    return nullptr;
}

void TextWarnRuleManage::TextWarnRuleManage::.timer_thread_function() 
{
    while(m_start)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        timeOut();
    }
}

void TextWarnRuleManage::setCurrentRule(TextWarnRule *r)
{
    if(r == nullptr)
    {
        stopThread();//没有警告信息就停止定时器
    }
    else
    {
        startThread();//新的信息显示重启定时器
    }
 
    if(m_callFun != nullptr)
    {   
        if(r != nullptr)
        {
            m_callFun(r->getValue());
        }
        else if(m_currentRule != nullptr)
        {
            WarnInfo info=m_currentRule->getPrevValue();
            info.value=0;
            m_callFun(info);
        }
        
    }
    m_currentRule = r;
}

void TextWarnRuleManage::SetCallWarnInfoFun(CallWarnInfoFun fun) 
{
    m_callFun = fun;
}

void TextWarnRuleManage::startThread() 
{
    m_start=true;
    if(timer_thread == nullptr)
        timer_thread = new std::thread(&TextWarnRuleManage::timer_thread_function, this);
}

void TextWarnRuleManage::stopThread()
{
    m_start=false;
    if(timer_thread != nullptr)
    {
        timer_thread->detach();
        delete timer_thread;
        timer_thread=nullptr;
    }
} 