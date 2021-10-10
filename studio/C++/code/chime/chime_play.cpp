#include "chime_play.h"
#include "../commondefine.hpp"

ChimePlay::ChimePlay::ChimePlay() 
{
    megaipc::PlayContorl contorl;
    contorl.playTime = 5;
    contorl.spaceTime = 5;
    contorl.id = DOOR_OPEN;
    playContorls[DOOR_OPEN]=contorl;

    contorl.playTime = 60;
    contorl.spaceTime = 90;
    contorl.cycle = 20;
    contorl.id = SEAT_BELT;
    playContorls[SEAT_BELT]=contorl;

    contorl.playTime = 5;
    contorl.spaceTime = 5;
    contorl.cycle = 9;
    contorl.id=LOW_KEY_POWER;
    playContorls[LOW_KEY_POWER]=contorl;

    timer_thread = new std::thread(&ChimePlay::timer_thread_function, this);    
}

void ChimePlay::ChimePlay::timer_thread_function() 
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        signal_process_logic();
    }    
}

void ChimePlay::ChimePlay::signal_process_logic() 
{
    for(auto iter = playContorls.begin(); iter != playContorls.end(); iter++)
    {
        if(currentTimeChanged(iter->first) !=-1)
        {
            play_process(iter->second);
            if(currentTimeChanged(iter->first) !=-1)
            {
                currentTimeChanged(iter->first,1,Add);
            }
        }
    }
}

void ChimePlay::ChimePlay::play_contorl(megaipc::ChimePlayInfo chimePlayInfo) 
{
    if(chimePlayInfo.isPlay())
    {
        if (currentTimeChanged(chimePlayInfo.id) == -1)
        {
            currentTimeChanged(chimePlayInfo.id, 0, Changed);
            playContorls[chimePlayInfo.id].status = true;
            play(true, chimePlayInfo.id);
        }
    }
    else
    {
        currentTimeChanged(chimePlayInfo.id,-1,Changed);
        playContorls[chimePlayInfo.id].status = false;
        play(false,chimePlayInfo.id);
    }
}

void ChimePlay::ChimePlay::play(bool isPlay,const int &id) 
{
    if(isPlay)
    {
        COUT("play audio id"<<id)
    }
    else
    {
         COUT("stop audio id"<<id)
    }
}

void ChimePlay::ChimePlay::play_process(megaipc::PlayContorl &contorl) 
{
    int cTime = currentTimeChanged(contorl.id);
    int currentTime = cTime % (contorl.playTime + contorl.spaceTime);
    if (contorl.cycle != -1)
    {
        if (cTime > (contorl.playTime + contorl.spaceTime) * contorl.cycle)
        {
            play(false, contorl.id);
            currentTimeChanged(contorl.id, -1, Changed);
            contorl.status = false;
            return;
        }
    }
    else
    {
        currentTimeChanged(contorl.id, currentTime, Changed);
    }
    if(currentTime < contorl.playTime && !contorl.status)
    {
        play(true,contorl.id);
        contorl.status = true;
    }
    else if(currentTime >= contorl.playTime && contorl.status)
    {
        play(false,contorl.id);
        contorl.status = false;
    }
}


int ChimePlay::ChimePlay::currentTimeChanged(const int &id, const int &value, const CurrentTimeStatus &status) 
{
    std::lock_guard<std::mutex> lk(current_mutex);
    if(status == Add)
    {
        playContorls[id].currentTime++;
    }
    else if(status == Changed)
    {
        playContorls[id].currentTime=value;
    }
    return playContorls[id].currentTime;
}
