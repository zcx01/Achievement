#ifndef DERIVE_RULE
#define DERIVE_RULE
#include "text_warn_rule.hpp"

class W1TextWarnRule : public LoopTextWarnRule
{
public:
    using LoopTextWarnRule::LoopTextWarnRule;
    int grade(){return WarnGrade::W1;}
};

class W2TextWarnRule : public TimeLoopTextWarnRule
{
public:
    using TimeLoopTextWarnRule::TimeLoopTextWarnRule;
    int grade(){return WarnGrade::W2;}
    int autoHideTime(){return 8;}
};

class OP1TextWarnRule : public TimeLoopTextWarnRule
{
public:
    using TimeLoopTextWarnRule::TimeLoopTextWarnRule;
    int grade(){return WarnGrade::OP1;}
    int autoHideTime(){return 8;}
};

class D1TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::D1;}
};

class D2TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::D2;}
};

class OP2TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::OP2;}
    int autoHideTime(){return 5;}
};

class OP3TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::OP3;}
};

class OP4TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::OP4;}
};

class OP5TextWarnRule : public SingleTextWarnRule
{
public:
    using SingleTextWarnRule::SingleTextWarnRule;
    int grade(){return WarnGrade::OP5;}
};
#endif // DERIVE_RULE
