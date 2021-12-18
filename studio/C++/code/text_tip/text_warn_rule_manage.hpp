#ifndef TEXTWARNRULEMANAGE_H
#define TEXTWARNRULEMANAGE_H

/**
 * 文字警告规则
 *
 * */
#include <vector>
#include <map>
#include <thread>
#include "structs/text_warn_define.h"
#include <mutex>

class TextWarnRule;

class TextWarnRuleManage
{
public:
    explicit TextWarnRuleManage();
    ~TextWarnRuleManage();

    bool addWarnInfo(const std::string &grade,WarnInfo &info);

    void SetCallWarnInfoFun(CallWarnInfoFun fun);

private:
    void timer_thread_function();

    void timeOut();

    TextWarnRule * createRule(const int &grade);

    TextWarnRule * getRuleByGrade(const int &grade);

    void startThread();
    
    void stopThread();

    void setCurrentRule(TextWarnRule *r);

    std::vector<TextWarnRule*>    m_warnRule;
    TextWarnRule*                 m_currentRule=nullptr;
    std::thread*                  timer_thread=nullptr;
    bool                          m_start=false;
    CallWarnInfoFun               m_callFun=nullptr;
    std::mutex                    m_mtx;
};

#endif // TEXTWARNRULEMANAGE_H
