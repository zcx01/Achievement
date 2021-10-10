#ifndef CHIME_PLAY__
#define CHIME_PLAY__
#include "structs/ic_chime_info.h"
#include <thread>
#include <memory>
#include <unordered_map>
#include <mutex>

class ChimePlay
{
public:
    ChimePlay();

    void play_contorl(megaipc::ChimePlayInfo chimePlayInfo);
    
private:

    enum CurrentTimeStatus
    {
        Add,    //自增
        Changed,//改变
        Get     //获取
    };
    
    void signal_process_logic();

    void timer_thread_function();

    void play_process(megaipc::PlayContorl &contorl);

    void play(bool isPlay, const int &id);

    int  currentTimeChanged(const int &id,const int &value=-1,const CurrentTimeStatus &status=Get);

    std::thread *timer_thread = nullptr;

    std::unordered_map<int,megaipc::PlayContorl> playContorls;

    std::mutex current_mutex;
};

#endif