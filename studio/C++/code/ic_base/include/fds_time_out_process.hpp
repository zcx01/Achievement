#pragma once

#include <thread>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

using FdsTimeOutProCallFun = std::function<void(float)>;

#define START_TIMING(CallFun) if(time_out_process == nullptr)\
{\
	time_out_process = std::make_shared<FdsTimeOutProcess>();\
	time_out_process->setCallFun(std::bind(CallFun, this, std::placeholders::_1));\
}

#define CANCEL_TIMING if(time_out_process != nullptr)\
{\
	time_out_process->setCancel(true);\
}

//异常处理判断
class FdsTimeOutProcess : public std::enable_shared_from_this<FdsTimeOutProcess>
{
public:

    FdsTimeOutProcess();

    void start();

    virtual ~FdsTimeOutProcess();

    void setCallFun(FdsTimeOutProCallFun fun);

    //设置间隔
    void setTimeSpace(const int &space);

    //设置值
    void setValue(const float &v);

    //设置取消
    void setCancel(const bool &s);

    //设置是否是循化
    void setLoop(const bool &loop);

    /**
     * @brief 是否结束
     * 
     * @return true ：结束
     * @return false ：没有结束
     */
    bool isEnd();

private:
    void timer_thread_fun();

    void stop();

    int timeSpace = 1000;

    FdsTimeOutProCallFun call_fun;

    std::thread *timer_thread = nullptr;

    float value = 0;

    bool is_loop = false;

    bool is_end = true;

    std::mutex m_mutex;

    std::unordered_map<std::thread*,uint64_t> t_thread_s;

    uint64_t timer_id = 0;
};
