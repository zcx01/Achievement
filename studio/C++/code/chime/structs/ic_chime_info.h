#ifndef IC_CHIME_INFO_H__O
#define IC_CHIME_INFO_H__O

#include <stdint.h>
#include <string>
#include <functional>
#include <vector>
#include "../../nlohmann/json.hpp"

#define READY_ID 105
#define POWER_STATUS 107
#define GEAR_SHIFT 110
#define SEAT_BELT 111
#define DOOR_OPEN 109
#define UNLOCK_MODE_CONVER 112  
#define LOW_KEY_POWER 102
#define KEY_LEARN 113

namespace megaipc
{
    /**
     * @brief 蜂鸣操作
     */
    enum ChimeInfoState {
        CHIMEINFO_STOP  = 0,   // 停止
        CHIMEINFO_START = 1,   // 启动
    };

    /** @brief 蜂鸣/语音信息 */
    struct ChimeInfo
    {
        uint32_t value;            /*! 数值 */
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChimeInfo, value);
    };

    struct ChimePlayInfo
    {
        int id = 0;
        int state=1;
        std::vector<int> playValues;
        bool isPlay()
        {
            return std::find(playValues.begin(),playValues.end(),state) != playValues.end();
        }
    };

    using ChimeFun = std::function<void(ChimePlayInfo)>;

    struct ChimeProcess
    {
        ChimeFun fun = nullptr;
        ChimePlayInfo playInfo;
    };

    struct PlayContorl
    {
        int cycle=-1;       //周期(-1表示一直放)
        int playTime=100;   //播放的时间
        int spaceTime=100;  //间隔时间
        int id=0;           //播放的id

        int currentTime = -1; //当前的时间（单位100ms进一,不等于-1是开始播放）
        bool status = false;//播放的状态
    };
    
}

#endif