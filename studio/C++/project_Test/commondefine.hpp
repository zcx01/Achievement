#ifndef COMMONDEFINE
#define COMMONDEFINE

#include <iostream>
#include <vector>
#include <list>
#include <map>

#define COUT(V) std::cout << __LINE__ << " ----  " << V << std::endl;

template <typename T0, typename... T>
void TB_LOG_INFO(T0 t0, T... t)
{
    std::cout << t0 << " ";
    if constexpr (sizeof...(t) > 0)
        TB_LOG_INFO(t...);
    else
        std::cout << std::endl;
}

template <typename T0, typename... T>
void TB_LOG_DEBUG(T0 t0, T... t)
{
    std::cout << t0 << " ";
    if constexpr (sizeof...(t) > 0)
        TB_LOG_INFO(t...);
    else
        std::cout << std::endl;
}

template <typename T0, typename... T>
void TB_LOG_ERROR(T0 t0, T... t)
{
    std::cout << t0 << " ";
    if constexpr (sizeof...(t) > 0)
        TB_LOG_INFO(t...);
    else
        std::cout << std::endl;
}

template <typename T>
void COUTI(T c)
{
    std::cout << __LINE__ << " ----  ";
    for (auto i : c)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

template <typename T, typename U>
void COUTMAP(std::map<T, U> c)
{
    std::cout << __LINE__ << " ----  ";
    for (auto i : c)
    {
        std::cout << i.first << " ";
    }
    std::cout << "\n";
}

static void printHex(const uint8_t *data, uint8_t len)
{
    char buff[512] = {0};
    for (int i = 0; i < len; i++)
    {
        sprintf(buff + i*3, "%02x ", data[i]);
    }
    printf("%s\n", buff);
}
// vector<string> v = split(s, ",*"); //可按多个字符来分隔;

#endif  //COMMONDEFINE