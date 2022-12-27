#include "ctest.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "navi_roads_def.h"
//道路信息
struct RoadLaneInfo
{
    uint8_t front=0;
    uint8_t back=0;
    uint8_t frontEx=0;
    uint8_t backEx=0;
};
ctestTest::ctestTest(/* args */) 
{
    RoadLaneInfo navi_road;
    navi_road.front = 255;
    navi_road.back = 11;
    uint32_t road_info_id = (navi_road.front << 24) + (navi_road.back << 16) + (navi_road.frontEx << 8) + navi_road.backEx;
    COUT(road_info_id)
    COUT(NaviRoadsIdEnum::NaviRoadsIdEnum_36)
}

CUSTOMEGISTER(ctest,ctestTest)