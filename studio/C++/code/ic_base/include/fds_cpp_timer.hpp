#pragma once

#include <string>
#include "fds_time_out_process.hpp"
#include <mutex>
#include <unordered_map>

namespace fds
{
    class fds_cpp_timer
    {
    public:
        fds_cpp_timer(/* args */);

        int add(int fristTime,FdsTimeOutProCallFun fun,int spaceTime=0);

        void remove(int id);

        bool is_exist(int id);

        void reset(int id);

    private:
        struct CallBackFunInfo
        {
            int count=0;
            int spaceTime=0;
            bool is_loop=false;
            bool is_reset=false;
            bool is_remove = false;
            FdsTimeOutProCallFun fun;
        };
        
        void time_out(float value);

        std::shared_ptr<FdsTimeOutProcess> time_out_process = nullptr;

        std::unordered_map<int,CallBackFunInfo> call_back_funs;

        std::mutex m_mutex;

        uint32_t all_id=0;

    };

    fds_cpp_timer* getTimer();
}