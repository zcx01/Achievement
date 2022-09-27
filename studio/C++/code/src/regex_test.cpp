#include "regex_test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <regex>

RegexTest::RegexTest(/* args */) 
{
    std::string test="CANSIG_GW_2A4__LCDAR_RCTAEnableStatus_g";
    std::regex txt_regex("[a-zA-Z0x0-9]+");
    COUT(std::regex_match(test,txt_regex));//当完全匹配成功时，会返回 true，否则返回 false

    //获取匹配的结果
    std::smatch base_match;
    std::regex_search(test,base_match,txt_regex);//寻找第一个与正则表达式匹配的子序列
    COUT(base_match.str()); 

    for (std::sregex_iterator it(test.begin(), test.end(), txt_regex), end_it; it != end_it; ++it)
    {
        COUT(it->str());
    }
}

CUSTOMEGISTER(RegexTest,RegexTest)