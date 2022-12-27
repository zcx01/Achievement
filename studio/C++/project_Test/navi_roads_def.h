#ifndef NAVI_ROADS_DEF_H
#define NAVI_ROADS_DEF_H

#include <stdint.h>
#include <cassert>
#include <iostream>
#include <enum.h>

// 直行
#define LANE_AHEAD 0U
// 左转
#define LANE_LEFT 1U
// 直行+左转
#define LANE_AHEAD_LEFT 2U
// 右转
#define LANE_RIGHT 3U
// 直行+右转
#define LANE_AHEAD_RIGHT 4U
// 左掉头
#define LANE_LU_TURN 5U
// 左转+右转
#define LANE_LEFT_RIGHT 6U
// 直行+左转+右转
#define LANE_AHEAD_LEFT_RIGHT 7U
// 右掉头
#define LANE_RU_TURN 8U
// 直行+左掉头
#define LANE_AHEAD_LU_TURN 9U
// 直行+右掉头
#define LANE_AHEAD_RU_TURN 10U
// 左转+左掉头
#define LANE_LEFT_LU_TURN 11U
// 右转+右掉头
#define LANE_RIGHT_RU_TURN 12U
// （左）直行
#define LANE_LEFT_IN_AHEAD 13U
// （左）左转+左掉头
#define LANE_LEFT_IN_LEFT_LU_TURN 14U
// 保留
#define LANE_RESERVED 15U
// 直行+左转+左掉头
#define LANE_AHEAD_LEFT_LU_TURN 16U
// 右转+右掉头（扩展）
#define LANE_RIGHT_RU_TURN_EX 17U
// 左转+右掉头
#define LANE_LEFT_RU_TURN 18U
// 直行+右转+右掉头
#define LANE_AHEAD_RIGHT_RU_TURN 19U
// 左转+左掉头（扩展）
#define LANE_LEFT_LU_TURN_EX 20U
// 公交车道
#define LANE_BUS 21U
// 空车道
#define LANE_EMPTY 22U
// 可变车道
#define LANE_VARIABLE 23U
// 无对应车道
#define LANE_NULL 255U

#define EXT_LANE_NORMAL 0U       /**< 普通 ，即无扩展车道*/
#define EXT_LANE_LEFT 1U         /**< 左扩展 */
#define EXT_LANE_RIGHT 2U        /**< 右扩展 */
#define EXT_LANE_LEFTNARROW 26U  /**< 左侧车道变窄 */
#define EXT_LANE_RIGHTNARROW 27U /**< 右侧车道变窄 */

BETTER_ENUM(NaviRoadsIdEnum, uint32_t,
    /* [[[cog
    import cog,json
    with open("navi_roads_config.json", "r") as f:
        json_content = json.loads(f.read())
        index=0
        for item in json_content:
            index=index+1
            out_line = '\nNaviRoadsIdEnum_{id} = ({front}<<24)+({back}<<16)+({front_ex}<<8)+{back_ex}{dot}'.format(
                        id=item['id'],
                        front=item['front'],
                        back=item['back'],
                        front_ex=item['front_ex'],
                        back_ex=item['back_ex'],
                        dot = ('' if index==len(json_content) else ','))
            cog.out(out_line)
            
    ]]] */

    NaviRoadsIdEnum_0 = (LANE_AHEAD<<24)+(LANE_AHEAD<<16)+(LANE_AHEAD<<8)+LANE_AHEAD,
    NaviRoadsIdEnum_1 = (LANE_NULL<<24)+(LANE_AHEAD<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_2 = (LANE_AHEAD<<24)+(LANE_AHEAD<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_3 = (LANE_NULL<<24)+(LANE_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_4 = (LANE_LEFT<<24)+(LANE_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_5 = (LANE_NULL<<24)+(LANE_AHEAD_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_6 = (LANE_AHEAD_LEFT<<24)+(LANE_AHEAD_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_7 = (LANE_AHEAD<<24)+(LANE_AHEAD_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_8 = (LANE_LEFT<<24)+(LANE_AHEAD_LEFT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_9 = (LANE_NULL<<24)+(LANE_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_10 = (LANE_RIGHT<<24)+(LANE_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_11 = (LANE_NULL<<24)+(LANE_AHEAD_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_12 = (LANE_AHEAD_RIGHT<<24)+(LANE_AHEAD_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_13 = (LANE_AHEAD<<24)+(LANE_AHEAD_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_14 = (LANE_RIGHT<<24)+(LANE_AHEAD_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_15 = (LANE_NULL<<24)+(LANE_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_16 = (LANE_LU_TURN<<24)+(LANE_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_17 = (LANE_NULL<<24)+(LANE_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_18 = (LANE_LEFT_RIGHT<<24)+(LANE_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_19 = (LANE_LEFT<<24)+(LANE_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_20 = (LANE_RIGHT<<24)+(LANE_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_21 = (LANE_NULL<<24)+(LANE_AHEAD_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_22 = (LANE_AHEAD_LEFT_RIGHT<<24)+(LANE_AHEAD_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_23 = (LANE_AHEAD<<24)+(LANE_AHEAD_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_24 = (LANE_LEFT<<24)+(LANE_AHEAD_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_25 = (LANE_RIGHT<<24)+(LANE_AHEAD_LEFT_RIGHT<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_26 = (LANE_NULL<<24)+(LANE_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_27 = (LANE_RU_TURN<<24)+(LANE_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_28 = (LANE_NULL<<24)+(LANE_AHEAD_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_29 = (LANE_AHEAD_LU_TURN<<24)+(LANE_AHEAD_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_30 = (LANE_AHEAD<<24)+(LANE_AHEAD_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_31 = (LANE_LU_TURN<<24)+(LANE_AHEAD_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_32 = (LANE_NULL<<24)+(LANE_AHEAD_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_33 = (LANE_AHEAD_RU_TURN<<24)+(LANE_AHEAD_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_34 = (LANE_AHEAD<<24)+(LANE_AHEAD_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_35 = (LANE_RU_TURN<<24)+(LANE_AHEAD_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_36 = (LANE_NULL<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_37 = (LANE_LEFT_LU_TURN<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_38 = (LANE_LEFT<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_39 = (LANE_LU_TURN<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_40 = (LANE_NULL<<24)+(LANE_RIGHT_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_41 = (LANE_RIGHT_RU_TURN<<24)+(LANE_RIGHT_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_42 = (LANE_RIGHT<<24)+(LANE_RIGHT_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_43 = (LANE_RU_TURN<<24)+(LANE_RIGHT_RU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_NORMAL,
    NaviRoadsIdEnum_44 = (LANE_NULL<<24)+(LANE_AHEAD<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_LEFT,
    NaviRoadsIdEnum_45 = (LANE_AHEAD<<24)+(LANE_AHEAD<<16)+(EXT_LANE_LEFT<<8)+EXT_LANE_LEFT,
    NaviRoadsIdEnum_46 = (LANE_NULL<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_LEFT,
    NaviRoadsIdEnum_47 = (LANE_LEFT_LU_TURN<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_LEFT<<8)+EXT_LANE_LEFT,
    NaviRoadsIdEnum_48 = (LANE_LEFT<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_NORMAL<<8)+EXT_LANE_LEFT,
    NaviRoadsIdEnum_49 = (LANE_LU_TURN<<24)+(LANE_LEFT_LU_TURN<<16)+(EXT_LANE_LEFT<<8)+EXT_LANE_LEFT
// [[[end]]]
)
#endif // NAVI_ROADS_DEF_H