#ifndef DERIVE_RULE
#define DERIVE_RULE
#include "text_warn_rule.hpp"

//循坏
class LoopTextWarnRule : public TextWarnRule
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

#endif // DERIVE_RULE
