#include "text_warn_rule_manage.hpp"
#include "derive_rule.hpp"
#include <algorithm>

TextWarnRuleManage::TextWarnRuleManage()
{
    for (int i = WarnGrade::W1; i < WarnGrade::count; i++)
    {
        m_warnRule.push_back(createRule(i));
    }
}

TextWarnRuleManage::~TextWarnRuleManage()
{
    for (auto iter = m_warnRule.begin(); iter != m_warnRule.end(); iter++)
    {
        delete *iter;
    }
}

bool TextWarnRuleManage::addWarnInfo(const std::string &grade, WarnInfo &info)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    int index = 0;
    try
    {
        index = WarnGrade::_from_string(grade.c_str())._to_index();
    }
    catch (...)
    {
        index = updateTopic(info);
        if(index == -1) return false;
    }
    auto rule = m_warnRule[index];
    if (rule != nullptr)
    {
        info.grade = rule->grade();
        bool status = rule->addWarnInfo(info);
        if (status && (m_currentRule == nullptr || (info.immediately && !m_currentRule->getValue().immediately) ) )
        {
            setCurrentRule(rule);
        }
        return status;
    }
    return false;
}


void TextWarnRuleManage::timeOut()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_currentRule != nullptr)
    {
        TimeChangeResult result = m_currentRule->changed();
        //打断rule
        if (result == TimeChangeResult::MinTime)
        {
            /***
             * 
             * interrupt 如果是为空，不会return，会走优先级的打断
             * */
            std::vector<int> interrupt = m_currentRule->Interrupt();
            std::sort(interrupt.begin(), interrupt.end(), [](const int &f, const int &t)
                      { return t < f; });
            std::vector<TextWarnRule *> rules;
            for (auto inter : interrupt)
            {
                rules.push_back(getRuleByGrade(inter));
            }
            for (auto rule : rules)
            {
                if (rule != nullptr && rule->isNewWarn() && !rule->isEmpty())
                {
                    setCurrentRule(rule);
                    return;
                }
            }
        }
        else if (result == TimeChangeResult::Runing)
        {
            return;
        }
        else if (result == TimeChangeResult::Finish)
        {
        }
    }

    for (auto rule : m_warnRule)
    {
        if (rule != nullptr && !rule->isEmpty())
        {
            if (m_currentRule == nullptr)
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
    case WarnGrade::OP5:
        return new OP5TextWarnRule;
    case WarnGrade::OP4:
        return new OP4TextWarnRule;
    case WarnGrade::OP3:
        return new OP3TextWarnRule;
    case WarnGrade::OP2:
        return new OP2TextWarnRule;
    case WarnGrade::D2:
        return new D2TextWarnRule;
    case WarnGrade::D1:
        return new D1TextWarnRule;
    case WarnGrade::OP1:
        return new OP1TextWarnRule;
    case WarnGrade::W2:
        return new W2TextWarnRule;
    case WarnGrade::W1:
        return new W1TextWarnRule;
    }
    return nullptr;
}

TextWarnRule *TextWarnRuleManage::getRuleByGrade(const int &grade)
{
    for (auto rule : m_warnRule)
    {
        if (rule->grade() == grade)
        {
            return rule;
        }
    }
    return nullptr;
}

void TextWarnRuleManage::TextWarnRuleManage::timer_thread_function()
{
    while (m_start)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        timeOut();
    }
}

void TextWarnRuleManage::setCurrentRule(TextWarnRule *r)
{
    if (r == nullptr)
    {
        stopThread(); //没有警告信息就停止定时器
    }
    else
    {
        startThread(); //新的信息显示重启定时器
    }
    if (m_currentRule != nullptr && m_currentRule != r)
    {
        m_currentRule->dealInterrupt();
    }
    if (m_callFun != nullptr)
    {
        if (r != nullptr)
        {
            m_callFun(r->getValue());
        }
        else if (m_currentRule != nullptr)
        {
            WarnInfo info = m_currentRule->getPrevValue();
            info.value = 0;
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
    m_start = true;
    if (timer_thread == nullptr)
        timer_thread = new std::thread(&TextWarnRuleManage::timer_thread_function, this);
}

void TextWarnRuleManage::stopThread()
{
    m_start = false;
    if (timer_thread != nullptr)
    {
        timer_thread->detach();
        delete timer_thread;
        timer_thread = nullptr;
    }
}


int TextWarnRuleManage::updateTopic(WarnInfo &info) 
{
    for (auto rule : m_warnRule)
    {
        if (rule != nullptr && !rule->isEmpty())
        {
            auto grade = rule->removeWarnInfo(info);
            if (grade != -1)
            {
                return grade;
            }
        }
    }
    return -1;
}
