#include "thread.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <future>

bool isStop = false;
std::packaged_task<void()> task_s;
void testPackaged_task()
{
    //将一个返回值为7的lambda表达式封装在 task 中
    // std::packaged_task 的模板参数为要封装的函数返回值类型
    // std::packaged_task<int()> task([](){return 7;});
    std::packaged_task<void()> task([]()
                                    {
                                        int index = 0;
                                        while (index < 20)
                                        {
                                            COUT(index)
                                            index++;
                                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                        } });
    task();//执行
    // task_s.swap(task); //task_s();可以在函数外部执行
}

void testFuture()
{
    std::packaged_task<int()> task([]()
                                    {
                                        int index = 0;
                                        while (index < 20)
                                        {
                                            COUT(index)
                                            index++;
                                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                        }
                                        return index;
                                    });
    std::future<int> result =  task.get_future();
    std::thread(std::move(task)).detach();//这里就执行了
    COUT("wait ...")
    result.wait();// 在此设置屏障，阻塞到期物的完成
    COUT("done!")
    COUT("futrue result is " << result.get())//获取返回的结果
}

threadTest::threadTest(/* args */)
{
    // time_thread = new std::thread(&threadTest::timeOut,this);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // COUT(time_thread->get_id());
    // time_thread->detach();
    testFuture();
    
}

void threadTest::timeOut() 
{
    int index = 0;
    while (!isStop)
    {
        COUT(index)
        index++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}


CUSTOMEGISTER(thread,threadTest)
