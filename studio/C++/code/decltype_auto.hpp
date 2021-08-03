#pragma once
#include <string>

class DecltypeAutoTest
{
private:
    /* data */
public:
    DecltypeAutoTest(/* args */);
};

class decltype_auto
{
private:
    /* data */
public:
    decltype_auto(/* args */);

    // decltype(auto) look_up_a_string_1();

    // decltype(auto) look_up_a_string_2();

// private:
    std::string lookup1();
    std::string &lookup2();

    std::string str;
};
