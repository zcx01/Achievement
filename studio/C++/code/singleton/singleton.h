/**
 * @file singleton.h
 * @brief Singleton template definition
 * @date 2021-05-07
 * @copyright Copyright (c) 2021 Megatronix
 */
#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * @brief 单例模板 
 * 需要使用单例模式的类型继承该模板即可实现单例化
 * @tparam T The type of the singleton object
 */
template<typename T>
class Singleton {
public:
    static T& instance();

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    struct Token {};
    Singleton() {}
};

#include <memory>
template<typename T>
T& Singleton<T>::instance()
{
    static T instance{Token{}};
    return instance;
}

#endif // !SINGLETON_H