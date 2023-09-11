/**
* @file         ./out/bigsur_c385/qnx/libecu_config.h
* @author       Binxin.cao
* @version      V20230615
* @date         2023.06.15
* @brief         
* @note          
* @attention    COPYRIGHT MEGA
**/

#ifndef __LIBECU_CONFIG_H
#define __LIBECU_CONFIG_H


#include <stdint.h>
#include <stdbool.h>


#define ECU_TABLE_USER_VEHICLE_MODEL                            0 /*车型配置*/
#define ECU_TABLE_USER_CRUISE                                   1 /*定速巡航*/
#define ECU_TABLE_USER_FCW                                      2 /*前碰撞预警*/
#define ECU_TABLE_USER_AEB_CI                                   3 /*自动紧急刹车AEB-C/I（车辆）*/
#define ECU_TABLE_USER_ACC_SG                                   4 /*停走自适应巡航（ACC S&G）*/
#define ECU_TABLE_USER_LDW                                      5 /*车道偏离警告系统*/
#define ECU_TABLE_USER_AEB_P                                    6 /*行人识别自动紧急刹车（AEB-P）*/
#define ECU_TABLE_USER_TSR                                      7 /*交通标志识别*/
#define ECU_TABLE_USER_IACC                                     8 /*集成式自适应IACC*/
#define ECU_TABLE_USER_LKA                                      9 /*车道保持*/
#define ECU_TABLE_USER_PARALLEL_ASSIST                          10 /*并线辅助*/
#define ECU_TABLE_USER_APA                                      11 /*自动泊车APA*/
#define ECU_TABLE_USER_RVC                                      12 /*内置倒车影像*/
#define ECU_TABLE_USER_RDA                                      13 /*后视野辅助影像*/
#define ECU_TABLE_USER_THERMOSTATIC_CABIN                       14 /*恒温座舱*/
#define ECU_TABLE_USER_DVR                                      15 /*内置行车记录仪 DVR*/
#define ECU_TABLE_USER_AVM                                      16 /*内置360°高清全景影像*/
#define ECU_TABLE_USER_FATIGUE_MONITOR                          17 /*疲劳检测*/
#define ECU_TABLE_USER_FACEID                                   18 /*人脸识别身份认证*/
#define ECU_TABLE_USER_INCABIN_MONITOR                          19 /*车内监控*/
#define ECU_TABLE_USER_GESTURE_RECOGNITION                      20 /*手势识别*/
#define ECU_TABLE_USER_HOLOGRAPHY                               21 /*全息投影*/
#define ECU_TABLE_USER_AI                                       22 /*实体AI交互*/
#define ECU_TABLE_USER_VOICE_ASSISTANT                          23 /*语音精灵*/
#define ECU_TABLE_USER_AUTO_BEAM                                24 /*智能远近光灯*/
#define ECU_TABLE_USER_AC_ZONE                                  25 /*空调温区*/
#define ECU_TABLE_USER_PM25_MONITOR                             26 /*车内外空气质量监控（PM2.5传感器）*/
#define ECU_TABLE_USER_PM25_FILTER                              27 /*PM2.5高效过滤功能*/
#define ECU_TABLE_USER_PLASMA                                   28 /*等离子发生器*/
#define ECU_TABLE_USER_AR_NAVIGATION                            29 /*AR-实景导航*/
#define ECU_TABLE_USER_WIRELESS_CHARGE                          30 /*无线充电*/
#define ECU_TABLE_USER_KEY_TYPE                                 31 /*钥匙类型*/
#define ECU_TABLE_USER_FM                                       32 /*收音机*/
#define ECU_TABLE_USER_SPEAKER_NUMBER                           33 /*扬声器数量*/
#define ECU_TABLE_USER_LANGUAGE                                 34 /*语言类型*/
#define ECU_TABLE_USER_STEERING                                 35 /*方向盘类型*/
#define ECU_TABLE_USER_TPMS                                     36 /*胎压监测类型*/
#define ECU_TABLE_USER_HUD                                      37 /*HUD类型*/
#define ECU_TABLE_USER_NAP                                      38 /*小憩模式*/
#define ECU_TABLE_USER_BACK_CARE                                39 /*后排关怀模式*/
#define ECU_TABLE_USER_CAMPING                                  40 /*露营模式*/
#define ECU_TABLE_USER_AUTO_WASH                                41 /*自动洗车模式*/
#define ECU_TABLE_USER_SMOKING                                  42 /*抽烟模式*/
#define ECU_TABLE_USER_WHIRL_SCREEN                             43 /*旋转屏*/
#define ECU_TABLE_USER_MIC_NUMBER                               44 /*声源定位（麦克风数量）*/
#define ECU_TABLE_USER_MIRROR_MEMORY                            45 /*后视镜位置记忆*/
#define ECU_TABLE_USER_MIRROR_FOLD                              46 /*后视镜电动折叠*/
#define ECU_TABLE_USER_ELECTRIC_TAILGATE                        47 /*电动后背门*/
#define ECU_TABLE_USER_AMB_TYPE                                 48 /*LED氛围灯类型*/
#define ECU_TABLE_USER_DRIVERSEAT_HEAT                          49 /*主驾座椅加热*/
#define ECU_TABLE_USER_DRIVERSEAT_VENT                          50 /*主驾座椅通风*/
#define ECU_TABLE_USER_PASSENGERSEAT_HEAT                       51 /*副驾座椅加热*/
#define ECU_TABLE_USER_PASSENGERSEAT_VENT                       52 /*副驾座椅通风*/
#define ECU_TABLE_USER_ICE_MODE                                 53 /*冰雪模式*/
#define ECU_TABLE_USER_RACE_MODE                                54 /*赛道模式*/
#define ECU_TABLE_USER_BONFIRE_MODE                             55 /*篝火模式*/
#define ECU_TABLE_USER_EXTERNAL_AMP                             56 /*外置功放*/
#define ECU_TABLE_USER_GUARD_MODE                               57 /*哨兵模式*/
#define ECU_TABLE_USER_APA70                                    58 /*APA7.0*/
#define ECU_TABLE_USER_NDA30                                    59 /*NDA3.0*/
#define ECU_TABLE_USER_STEERING_CFG                             60 /*方向盘按键配置*/
#define ECU_TABLE_USER_DRIVING_ASSISTANCE                       61 /*智能驾驶辅助*/
#define ECU_TABLE_USER_LCA                                      62 /*换道辅助*/
#define ECU_TABLE_USER_PILOT                                    63 /*领航智驾*/
#define ECU_TABLE_USER_LCA_MODE                                 64 /*换道模式*/
#define ECU_TABLE_USER_VOICE_TIPS                               65 /*语音提示*/
#define ECU_TABLE_USER_HAZARD_WARNING                           66 /*危险报警*/
#define ECU_TABLE_USER_SAFETY_WARNING                           67 /*安全提示*/
#define ECU_TABLE_USER_INFO_TTS                                 68 /*信息播报*/
#define ECU_TABLE_USER_NOA                                      69 /*高速公路辅助*/
#define ECU_TABLE_USER_TRAFFIC_CRUISE                           70 /*交通拥堵巡航*/
#define ECU_TABLE_USER_ISA                                      71 /*智能限速*/
#define ECU_TABLE_USER_OVER_SPEED_WARN                          72 /*超速预警*/
#define ECU_TABLE_USER_DEVIATION                                73 /*偏差值*/
#define ECU_TABLE_USER_LDW_LKA                                  74 /*车道偏离辅助模式*/
#define ECU_TABLE_USER_WARNING_TYPE                             75 /*预警方式*/
#define ECU_TABLE_USER_FCTA                                     76 /*前方横向预警*/
#define ECU_TABLE_USER_RCTA                                     77 /*倒车横向预警*/
#define ECU_TABLE_USER_RCW                                      78 /*后追尾预警*/
#define ECU_TABLE_USER_AEB                                      79 /*自动紧急制动*/
#define ECU_TABLE_USER_RCTB                                     80 /*倒车横向自动紧急制动*/
#define ECU_TABLE_USER_FCTB                                     81 /*前方横向自动紧急制动*/
#define ECU_TABLE_USER_TRAFFICLIGHT_ASSIST                      82 /*交通灯辅助*/
#define ECU_TABLE_USER_DOW                                      83 /*开门预警*/
#define ECU_TABLE_USER_DOW_VOICE                                84 /*开门预警语音提示*/
#define ECU_TABLE_USER_ADAS_MAP                                 85 /*ADAS地图*/
#define ECU_TABLE_USER_HIGHPRECISION_MAP                        86 /*高精度地图*/
#define ECU_TABLE_USER_VOICE_SET_SPEED                          87 /*语音设置巡航车速*/
#define ECU_TABLE_USER_VOICE_CHANGE_LANE                        88 /*语音控制换道*/
#define ECU_TABLE_USER_VOICE_IACC_HWA                           89 /*语音设置IACC/HWA权限开关*/
#define ECU_TABLE_USER_FATIGUE_WARNING                          90 /*脱眼/疲劳/接管报警语音提示*/
#define ECU_TABLE_USER_STARTED_WARNING                          91 /*起步提醒语音提示*/
#define ECU_TABLE_USER_DVR_EMERGENCY_RECORD                     92 /*行车辅助系统紧急事件记录需求或ADR需求（带ADS控制器车型）*/
#define ECU_TABLE_USER_DRIVING_ASSISTANCE_PUSH                  93 /*行车辅助系统主动推送*/
#define ECU_TABLE_USER_DISCHARGE_CUTOFF_QUANTITY                94 /*放电截止电量*/
#define ECU_TABLE_USER_AVAS_PWM                                 95 /*AVAS独立控制器*/
#define ECU_TABLE_USER_AVAS_A2B_SPEAKER                         96 /*AVAS-A2B扬声器*/
#define ECU_TABLE_USER_AVAS_SPEAKER                             97 /*AVAS-纯扬声器*/
#define ECU_TABLE_USER_POWER_MODE                               98 /*动力来源*/
#define ECU_TABLE_USER_LIGHT_COMITY                             99 /*灯光礼让*/
#define ECU_TABLE_USER_DRL                                      100 /*日间行车灯*/
#define ECU_TABLE_USER_SENSOR_LOCK                              101 /*感应解闭锁*/
#define ECU_TABLE_USER_CHARGE_COVER                             102 /*充电舱盖*/
#define ECU_TABLE_USER_CHRG_PILE_CNCT                           103 /*充电桩连接*/
#define ECU_TABLE_USER_SEAT_COMITY                              104 /*座椅礼让*/
#define ECU_TABLE_USER_FRONT_RADAR                              105 /*前雷达开关*/
#define ECU_TABLE_USER_MEB                                      106 /*低速自动紧急制动*/
#define ECU_TABLE_USER_STEERING_HEAT                            107 /*方向盘加热*/
#define ECU_TABLE_USER_WINDOW_ADJUSTMENT                        108 /*车窗开闭调节*/
#define ECU_TABLE_USER_ETHERNET_MODE                            109 /*新增-以太网配置*/
#define ECU_TABLE_USER_LAMP_PATTERN_ADJUSTMENT                  110 /*新增-位置灯图案设置*/
#define ECU_TABLE_USER_ENERGYUSAGE_QUIRY                        111 /*新增-能量流*/
#define ECU_TABLE_USER_INTERACTIVE_LAMP                         112 /*新增-交互灯*/
#define ECU_TABLE_USER_SCREEN_AUTOBRIGHTNESS                    113 /*新增-屏幕自动亮度调节*/
#define ECU_TABLE_USER_DMS                                      114 /*新增-DMS摄像头*/
#define ECU_TABLE_USER_CMS                                      115 /*新增-CMS摄像头*/
#define ECU_TABLE_USER_SUNROOF_TYPE                             116 /*新增-天窗类型*/
#define ECU_TABLE_USER_CHARGE_LIMIT                             117 /*新增-充电电量上限*/
#define ECU_TABLE_USER_REAR_AC                                  118 /*后排空调*/
#define ECU_TABLE_USER_GAS_CAP_SWITCH                           119 /*油箱盖开关*/
#define ECU_TABLE_USER_GLOVE_BOX                                120 /*手套箱*/
#define ECU_TABLE_USER_ENERGY_ANALYSIS                          121 /*能耗分析*/
#define ECU_TABLE_USER_WINTER_MODE                              122 /*冬季模式*/
#define ECU_TABLE_USER_AUTO_DEHUMIDIFER                         123 /*自动除湿*/
#define ECU_TABLE_USER_IC_VIEW_SWITCH                           124 /*仪表卡片界面切换*/
#define ECU_TABLE_USER_AMBIENT_LIGHT_TURN                       125 /*车内背景光调节*/
#define ECU_TABLE_USER_REAR_SEAT_BELT                           126 /*后排安全带*/
#define ECU_TABLE_USER_DRIVERSEAT_ADJUST                        127 /*主驾座椅电动调节（6向）*/
#define ECU_TABLE_USER_DRIVERSEAT_MEMORY                        128 /*主驾座椅记忆*/
#define ECU_TABLE_USER_DRIVER_CUSHION                           129 /*主驾坐垫倾角调节*/
#define ECU_TABLE_USER_DRIVERLUMBAR_ADJUST                      130 /*主驾腰部支撑调节*/
#define ECU_TABLE_USER_PASSENGERSEAT_ADJUST                     131 /*副驾座椅电动调节（4向）*/
#define ECU_TABLE_USER_OUTSIDE_DMS                              132 /*DMS 外置*/
#define ECU_TABLE_USER_DRIVING_TYPE                             133 /*驱动形式*/
#define ECU_TABLE_USER_FAST_CHARGE                              134 /*快充功能*/
#define ECU_TABLE_USER_TAIL                                     135 /*尾翼*/
#define ECU_TABLE_USER_HEADLAMP_HEIGHT_ADJUST                   136 /*大灯高度调节*/
#define ECU_TABLE_USER_MIRROR_AUTO_DIPPING                      137 /*外后视镜自动调整*/
#define ECU_TABLE_USER_DRIVERSEAT_MASSAGE                       138 /*主驾座椅按摩*/
#define ECU_TABLE_USER_PASSENGERSEAT_MASSAGE                    139 /*副驾座椅按摩*/
#define ECU_TABLE_USER_REARSEAT_ADJUST                          140 /*二排座椅调节形式*/
#define ECU_TABLE_USER_REARSEAT_HEAT                            141 /*二排座椅加热*/
#define ECU_TABLE_USER_REARSEAT_VENT                            142 /*二排座椅通风*/
#define ECU_TABLE_USER_REARSEAT_MASSAGE                         143 /*二排座椅按摩*/
#define ECU_TABLE_USER_FRAGRANCE                                144 /*香氛系统*/
#define ECU_TABLE_USER_NEGATIVE_ION                             145 /*负离子发生器*/
#define ECU_TABLE_USER_SOUND_SYSTEM                             146 /*音响系统*/
#define ECU_TABLE_USER_FUEL_COVER                               147 /*油箱盖开启方式*/
#define ECU_TABLE_USER_VEHICLE_NETWORK                          148 /*车联网*/
#define ECU_TABLE_USER_DRIVING_ASSISTANT                        149 /*行车助手*/
#define ECU_TABLE_USER_ETC                                      150 /*不停车收费系统*/
#define ECU_TABLE_USER_FCW_RCW                                  151 /*预碰撞安全系统FCW/后向碰撞预警RCW*/
#define ECU_TABLE_USER_FVSR                                     152 /*前车驶离提醒FVSR*/
#define ECU_TABLE_USER_AEB_MEB                                  153 /*自动紧急刹车AEB/低速紧急制动MEB*/
#define ECU_TABLE_USER_BSD                                      154 /*盲区监测系统BSD*/
#define ECU_TABLE_USER_ICA                                      155 /*集成式巡航ICA（TJA+HWA）*/
#define ECU_TABLE_USER_RCTA_RCTB                                156 /*后方交通横穿警示RCTA/后方交通横穿制动RCTB*/
#define ECU_TABLE_USER_JA                                       157 /*十字路口辅助JA*/
#define ECU_TABLE_USER_ISLC                                     158 /*智能限速控制ISLC*/
#define ECU_TABLE_USER_ESA                                      159 /*紧急转向辅助ESA*/
#define ECU_TABLE_USER_ELK                                      160 /*紧急车道保持ELK*/
#define ECU_TABLE_USER_TLC                                      161 /*触发式自动变道TLC*/
#define ECU_TABLE_USER_PDC                                      162 /*前、后部驻车雷达PDC*/
#define ECU_TABLE_USER_RPA                                      163 /*遥控泊车RPA*/
#define ECU_TABLE_USER_HPP                                      164 /*代客泊车HPP*/
#define ECU_TABLE_USER_RVM                                      165 /*远程挪车RVM*/
#define ECU_TABLE_USER_AIR_SUSPENSION                           166 /*空气悬架*/
#define ECU_TABLE_USER_CARCOLOR                                 167 /*车身颜色*/
#define ECU_TABLE_USER_EMS                                      168 /*发动机控制系统模块*/
#define ECU_TABLE_USER_BCM                                      169 /*车身控制模块*/
#define ECU_TABLE_USER_ICM                                      170 /*仪表模块*/
#define ECU_TABLE_USER_ABM                                      171 /*Airbag Module*/
#define ECU_TABLE_USER_ABS                                      172 /*防锁刹车系统*/
#define ECU_TABLE_USER_ESP                                      173 /*电子刹车*/
#define ECU_TABLE_USER_IMMO                                     174 /*防盗器*/
#define ECU_TABLE_USER_TCU1                                     175 /*TCU1*/
#define ECU_TABLE_USER_TCU2                                     176 /*TCU2*/
#define ECU_TABLE_USER_CLM                                      177 /*自动空调*/
#define ECU_TABLE_USER_EPS                                      178 /*电子助力转向*/
#define ECU_TABLE_USER_PEPS                                     179 /*无钥匙系统*/
#define ECU_TABLE_USER_SAS                                      180 /*SAS*/
#define ECU_TABLE_USER_RADAR                                    181 /*倒车雷达*/
#define ECU_TABLE_USER_TCU3                                     182 /*TCU3*/
#define ECU_TABLE_USER_TCU4                                     183 /*TCU4*/
#define ECU_TABLE_USER_EPB                                      184 /*电子驻车制动系统*/
#define ECU_TABLE_USER_RADIO_AREA                               185 /*RADIO_AREA*/
#define ECU_TABLE_USER_RAV                                      186 /*倒车辅助*/
#define ECU_TABLE_USER_AUTO_LIGHT                               187 /*自动灯*/
#define ECU_TABLE_USER_MAF                                      188 /*镜子自动折叠*/
#define ECU_TABLE_USER_VSAL                                     189 /*Vehicle Speed Auto lock*/
#define ECU_TABLE_USER_FCM                                      190 /*前置摄像头*/
#define ECU_TABLE_USER_PLG                                      191 /*Power Lift Gate*/
#define ECU_TABLE_USER_SPEAK_NUM                                192 /*扬声器数量*/
#define ECU_TABLE_USER_STEERING_MODE                            193 /*转向模式选择*/
#define ECU_TABLE_USER_EIPM_ON_CAN                              194 /*EIPM on CAN*/
#define ECU_TABLE_USER_RADIO_ANT_PARAM                          195 /*无线电天线*/
#define ECU_TABLE_USER_TIHU_CFG                                 196 /*IHUTIHU&DMC-IHU/TIHU Configuration*/
#define ECU_TABLE_USER_GRM_SWITCH                               197 /*GRM Switch*/
#define ECU_TABLE_USER_AVM_TYPE                                 198 /*AVM Type*/
#define ECU_TABLE_USER_NM_TYPE                                  199 /*NM Type*/
#define ECU_TABLE_USER_FRM                                      200 /*前置雷达*/
#define ECU_TABLE_USER_INTERAVTIVE_MODE                         201 /*IHU/TIHU&DMC-IHU/TIHU-Sequoia ICM Interactive Mode*/
#define ECU_TABLE_USER_PEPS_TYPE                                202 /*PEPS Type*/
#define ECU_TABLE_USER_MFS                                      203 /*Multi Function Switch*/
#define ECU_TABLE_USER_INTERIOR_LIGHT                           204 /*Interior Lighting*/
#define ECU_TABLE_USER_SCU                                      205 /*SCU*/
#define ECU_TABLE_USER_CWC                                      206 /*CWC*/
#define ECU_TABLE_USER_TIHU_CFG2                                207 /*IHU/TIHU Configuration2*/
#define ECU_TABLE_USER_FWH                                      208 /*Front windshield heating*/
#define ECU_TABLE_USER_ILT                                      209 /*Interior Lighting Type*/
#define ECU_TABLE_USER_ARKAMYS_ADVANCED                         210 /*Arkamys Advanced*/
#define ECU_TABLE_USER_AIPM_TFT                                 211 /*AIPM-TFT*/
#define ECU_TABLE_USER_WELCOME_FUNC                             212 /*Welcome function*/
#define ECU_TABLE_USER_AUTO_LOCK                                213 /*Go to unlock and leave the lock*/
#define ECU_TABLE_USER_INTELLIGENT_OPEN_TRUNK                   214 /*Intelligent open trunk*/
#define ECU_TABLE_USER_ATUO_DEFOG                               215 /*Auto defog*/
#define ECU_TABLE_USER_RADAR_DISPLAY                            216 /*雷达（Sequoia ICM上的雷达报警显示）*/
#define ECU_TABLE_USER_BT_KEY                                   217 /*BT Key*/
#define ECU_TABLE_USER_ACP                                      218 /*Audio Control PanelS*/
#define ECU_TABLE_USER_GET_TIME                                 219 /*Only get time from Bus(hour/minute/second)*/
#define ECU_TABLE_USER_CARPLAY                                  220 /*Carplay*/
#define ECU_TABLE_USER_QD_LINK                                  221 /*QD Link*/
#define ECU_TABLE_USER_ANDROID_AUTO                             222 /*Android Auto*/
#define ECU_TABLE_USER_ION                                      223 /*ION*/
#define ECU_TABLE_USER_ASSIST_LINE                              224 /*Assist line*/
#define ECU_TABLE_USER_REAR_RADAR_NUM                           225 /*Rear Radars Number*/
#define ECU_TABLE_USER_EAMP                                     226 /*EAMP*/
#define ECU_TABLE_USER_DRIVE_MODE_NUM                           227 /*Number of Drive Mode*/
#define ECU_TABLE_USER_CGW                                      228 /*CGW*/
#define ECU_TABLE_USER_APM                                      229 /*Anti Pinch Control Module*/
#define ECU_TABLE_USER_RADIO_AREA2                              230 /*Radio Area2*/
#define ECU_TABLE_USER_FACE_STYLE                               231 /*Face style*/
#define ECU_TABLE_USER_DISPLAY_TYPE                             232 /*Display Type*/
#define ECU_TABLE_USER_NAVIGATION_INFO                          233 /*Navigation Information*/
#define ECU_TABLE_USER_DRIVE_MODE_NUM2                          234 /*Number of Drive Mode2(IHU/TIHU)*/
#define ECU_TABLE_USER_SONY_SOUND                               235 /*SONY sound*/
#define ECU_TABLE_USER_SEAT                                     236 /*Seat Ventilating*/
#define ECU_TABLE_USER_LIGHTED_ROOF_RACK                        237 /*Lighted Roof Rack*/
#define ECU_TABLE_USER_SUNROOF                                  238 /*Sunroof*/
#define ECU_TABLE_USER_AVM_INTER_METHOD                         239 /*AVM Intergated Method */
#define ECU_TABLE_USER_CMOS_INTER_MODE                          240 /*CMOS Interactive Mode*/
#define ECU_TABLE_USER_SLAF                                     241 /*Speed Limit Assistance Function*/
#define ECU_TABLE_USER_BEIDOU                                   242 /*Beidou*/
#define ECU_TABLE_USER_TBOX_ECALL_MODULE                        243 /*Tbox/Ecall External module*/
#define ECU_TABLE_USER_FRONE_RADAR                              244 /*Front Radar*/
#define ECU_TABLE_USER_CVBOX                                    245 /*CVBOX*/
#define ECU_TABLE_USER_EPS_INTEGRATED_SAS                       246 /*EPS integrated SAS*/
#define ECU_TABLE_USER_RLCR                                     247 /*Rear Left Corner Radar*/
#define ECU_TABLE_USER_RRCR                                     248 /*Rear Right Corner Radar*/
#define ECU_TABLE_USER_CCP                                      249 /*Climate Control Panel*/
#define ECU_TABLE_USER_ECLM                                     250 /*电动空调*/
#define ECU_TABLE_USER_ISSS                                     251 /*Idle Start Stop System*/
#define ECU_TABLE_USER_SPEED_CTL_FUNC                           252 /*Speed Control Function*/
#define ECU_TABLE_USER_EMERGENCY_LANE_KEEPING                   253 /*Emergency Lane Keeping*/
#define ECU_TABLE_USER_LANE_DEPARTURE_PRE                       254 /*Lane Departure Prevention*/
#define ECU_TABLE_USER_TJA                                      255 /*Traffic Jam Assist*/
#define ECU_TABLE_USER_TLI                                      256 /*Traffic Light Identification*/
#define ECU_TABLE_USER_VOICE_RECOGNITION                        257 /*Voice Recognition*/
#define ECU_TABLE_USER_DRIVER_AWAY_INFO                         258 /*Driver Away Information*/
#define ECU_TABLE_USER_IES                                      259 /*Intelligent Evasion System*/
#define ECU_TABLE_USER_SLA                                      260 /*Speed Limit Assistance*/
#define ECU_TABLE_USER_SHU1D                                    261 /*SHU1D*/
#define ECU_TABLE_USER_SHU1P                                    262 /*SHU1P*/
#define ECU_TABLE_USER_SHU2L                                    263 /*SHU2L*/
#define ECU_TABLE_USER_SHU2R                                    264 /*SHU2R*/
#define ECU_TABLE_USER_RAVT                                     265 /*Reverse Assist Video Type*/
#define ECU_TABLE_USER_ECALL                                    266 /*ECALL*/
#define ECU_TABLE_USER_LHM                                      267 /*LHM*/
#define ECU_TABLE_USER_RHM                                      268 /*RHM*/
#define ECU_TABLE_USER_BDM                                      269 /*BDM*/
#define ECU_TABLE_USER_W_HUD                                    270 /*W-HUD*/
#define ECU_TABLE_USER_MIDRANGE_SPEAK_NUM                       271 /*Number of Midrange Loudspeaker*/
#define ECU_TABLE_USER_AR_HUD                                   272 /*AR-HUD*/
#define ECU_TABLE_USER_DRIVE_MODE                               273 /*Drive Mode*/
#define ECU_TABLE_USER_OMS                                      274 /*OMS*/
#define ECU_TABLE_USER_RMS                                      275 /*RMS*/
#define ECU_TABLE_USER_IDCU                                     276 /*IDCU*/
#define ECU_TABLE_USER_SMART_PHONE_KEY                          277 /*Smart Phone Key*/
#define ECU_TABLE_USER_RAIN_SENSOR                              278 /*Rain sensor sensitivity soft switch*/
#define ECU_TABLE_USER_WIPER_SOFT_SWITCH                        279 /*Intermittent wiper soft switch*/
#define ECU_TABLE_USER_COMBINATION_SWITCH_ASSY                  280 /*Combination Switch Assy(integration E-gear shift)*/
#define ECU_TABLE_USER_INTERIOR_ATMOSPHER_LEGHT                 281 /*Interior Atmosphere Light System*/
#define ECU_TABLE_USER_IMTERIOR_ATMOSPHER_LIGHT_TYPE            282 /*Interior Atmosphere Light Type*/
#define ECU_TABLE_USER_ICM_ABM                                  283 /*Sequoia ICM ABM*/
#define ECU_TABLE_USER_ICM_ABS                                  284 /*Sequoia ICM ABS*/
#define ECU_TABLE_USER_ICM_ESP                                  285 /*Sequoia ICM ESP*/
#define ECU_TABLE_USER_ICM_TCU1                                 286 /*TCU1(CVT19)*/
#define ECU_TABLE_USER_ICM_TCU2                                 287 /*TCU2 (6DCT)*/
#define ECU_TABLE_USER_ICM_CLM                                  288 /* Sequoia ICM CLM*/
#define ECU_TABLE_USER_ICM_EPS                                  289 /*Sequoia ICM EPS*/
#define ECU_TABLE_USER_ICM_PEPS                                 290 /* Sequoia ICM PEPS*/
#define ECU_TABLE_USER_IHU                                      291 /*Sequoia ICM IHU*/
#define ECU_TABLE_USER_ICM_TPMS                                 292 /*Sequoia ICM TPMS*/
#define ECU_TABLE_USER_ICM_CGW                                  293 /*Sequoia ICM CGW*/
#define ECU_TABLE_USER_ICM_EPB                                  294 /*Sequoia ICM EPB*/
#define ECU_TABLE_USER_ICM_AVM                                  295 /*Sequoia ICM AVM*/
#define ECU_TABLE_USER_ICM_BSD                                  296 /*Sequoia ICM BSD*/
#define ECU_TABLE_USER_ICM_LDW                                  297 /*Sequoia ICM LDW*/
#define ECU_TABLE_USER_ICM_PLG                                  298 /*Sequoia ICM PLG*/
#define ECU_TABLE_USER_FIRST_MAINTAIN                           299 /*First Maintain*/
#define ECU_TABLE_USER_MAINTAION_MILEAGE                        300 /*Maintain Mileage*/
#define ECU_TABLE_USER_FUEL_CONSUME_CORRECT                     301 /*Fuel Consumption Correct*/
#define ECU_TABLE_USER_ICM_RADAR                                302 /*Sequoia ICM Radar*/
#define ECU_TABLE_USER_ENGINE_FUEL_TYPE                         303 /*Engine Fuel Type*/
#define ECU_TABLE_USER_ICM_LANGUAGE                             304 /*Sequoia ICM Language*/
#define ECU_TABLE_USER_ICM_OVER_SPEED_WARN                      305 /*Sequoia ICM Over Speed Warning Function*/
#define ECU_TABLE_USER_SIMM                                     306 /*Second Interval Maintain Mileage*/
#define ECU_TABLE_USER_ICM_TCU3                                 307 /*TCU3(CVT25/CVT18)*/
#define ECU_TABLE_USER_ICM_FCM                                  308 /*Sequoia ICM FCM*/
#define ECU_TABLE_USER_ICM_FRM                                  309 /*Sequoia ICM FRM*/
#define ECU_TABLE_USER_ICM_REAR_RADAR_NUM                       310 /*Rear Radars Number*/
#define ECU_TABLE_USER_EMISSION_TYPE                            311 /*Emission Type*/
#define ECU_TABLE_USER_ICM_NAVIGATION_INFO                      312 /*Sequoia ICM Navigation Information*/
#define ECU_TABLE_USER_ICM_TCU4                                 313 /*Sequoia ICM TCU4(7DCT/DHT)*/
#define ECU_TABLE_USER_ESCL                                     314 /*ESCL(CAN)*/
#define ECU_TABLE_USER_EGS                                      315 /*EGS*/
#define ECU_TABLE_USER_ICM_MFS                                  316 /*Sequoia ICM MFS(LIN)*/
#define ECU_TABLE_USER_ICM_APA                                  317 /*Sequoia ICM APA*/
#define ECU_TABLE_USER_EPB_WORK_LOGIC                           318 /*EPB Work Logic*/
#define ECU_TABLE_USER_ICM_PEPS_TYPE                            319 /*Sequoia ICM PEPS_Type*/
#define ECU_TABLE_USER_EGS_TYPE                                 320 /*EGS Type*/
#define ECU_TABLE_USER_ICM_VEHICLE_TYPE                         321 /*Sequoia ICM Vehicle Type*/
#define ECU_TABLE_USER_ICM_LKA                                  322 /*Sequoia ICM LKA*/
#define ECU_TABLE_USER_ICM_DRIVE_MODE_NUM                       323 /*ICM Number of Drive Mode*/
#define ECU_TABLE_USER_DEFAULT_DRIVE_MODE                       324 /*Default drive mode*/
#define ECU_TABLE_USER_MAINTAION_MILEAGE2                       325 /*Maintain Mileage2*/
#define ECU_TABLE_USER_SIMM2                                    326 /*Second interval maintain mileage2*/
#define ECU_TABLE_USER_ICM_BMS                                  327 /*BMS*/
#define ECU_TABLE_USER_SPEED_LIMIT                              328 /*Speed Limit*/
#define ECU_TABLE_USER_ICM_FACE_STYLE                           329 /*Face Style*/
#define ECU_TABLE_USER_SRSBR_SWITCH                             330 /*Second Row SBR + Buckle switch*/
#define ECU_TABLE_USER_AWD                                      331 /*AWD*/
#define ECU_TABLE_USER_ICM_DRIVE_MODE_NUM2                      332 /*ICM Number of Drive Mode2(IHU/TIHU)*/
#define ECU_TABLE_USER_TRSBR_SWITCH                             333 /*Third Row SBR + Buckle switch*/
#define ECU_TABLE_USER_FUEL_TANK_CAPACITY                       334 /*fuel tank capacity*/
#define ECU_TABLE_USER_RLCR1                                    335 /*RLCR bit0*/
#define ECU_TABLE_USER_RLCR2                                    336 /*RLCR bit1*/
#define ECU_TABLE_USER_EBS                                      337 /*EBS*/
#define ECU_TABLE_USER_MAINTAION_MILEAGE3                       338 /*Maintain Mileage3*/
#define ECU_TABLE_USER_INIT_FUEL_CONSUME2                       339 /*Initial Fuel Consumption2*/
#define ECU_TABLE_USER_ICM_EMERGENCY_LANE_KEEPING               340 /*Sequoia ICM Emergency Lane Keeping*/
#define ECU_TABLE_USER_ICM_LANE_DEPARTURE_PRE                   341 /*Sequoia ICM Lane Departure Prevention*/
#define ECU_TABLE_USER_ICM_TJA                                  342 /*Sequoia ICM Traffic Jam Assist*/
#define ECU_TABLE_USER_ICM_SIMM3                                343 /*Second interval maintain mileage3*/
#define ECU_TABLE_USER_MODEL_CODE                               344 /*Model Code*/
#define ECU_TABLE_USER_BRAND                                    345 /*Brand*/
#define ECU_TABLE_USER_SUNROOF_ATMOSPHERE_LAMP                  346 /*Sunroof Atmosphere Lamp*/
#define ECU_TABLE_USER_STEERING_WHEEL_HEAT                      347 /*Steering Wheel Heating */
#define ECU_TABLE_USER_FTSR                                     348 /*Four tone speech recognition*/
#define ECU_TABLE_USER_OUTSIDE_SPEAKER                          349 /*车外扬声器*/
#define ECU_TABLE_USER_CFG_COMPASS                              350 /*指南针配置*/
#define ECU_TABLE_USER_CFG_ENGSPD_FILET_VAL_HIGH                351 /*滤波系数高8位*/
#define ECU_TABLE_USER_CFG_ENGSPD_FILET_VAL_LOW                 352 /*滤波系数低8位*/
#define ECU_TABLE_USER_CFG_ENGSPD_MAX_VAL_HIGH                  353 /*判断阀值高8位*/
#define ECU_TABLE_USER_CFG_ENGSPD_MAX_VAL_LOW                   354 /*判断阀值低8位*/
#define ECU_TABLE_USER_CFG_COOLANT_HOT_ON                       355 /*触发高温报警温度值*/
#define ECU_TABLE_USER_CFG_COOLANT_HOT_OFF                      356 /*水温高报警解除的温度值*/
#define ECU_TABLE_USER_REFULE_TIME_1                            357 /*加油延迟时间参数1*/
#define ECU_TABLE_USER_FUELLEVEL_SAMPLING                       358 /*燃油采样数据量*/
#define ECU_TABLE_USER_REFULE_DETECTION                         359 /*加油检测升数*/
#define ECU_TABLE_USER_REFULE_TIME_2                            360 /*加油延迟时间参数2*/
#define ECU_TABLE_USER_FUELLEVEL_DAMPING_1                      361 /*燃油阻尼参数1*/
#define ECU_TABLE_USER_REFULE_TIME_3                            362 /*加油延迟时间参数3*/
#define ECU_TABLE_USER_REFULE_TIME_4                            363 /*加油延迟时间参数4*/
#define ECU_TABLE_USER_FUELLEVEL_DAMPING_2                      364 /*燃油阻尼参数2*/
#define ECU_TABLE_USER_MAX_DIGITAL_SPEED                        365 /*最大车速*/
#define ECU_TABLE_USER_REFUEL_HYSTRESIS                         366 /*低燃油报警点缓冲值*/
#define ECU_TABLE_USER_CFG_ODO_FACTOR                           367 /*里程计算系数*/
#define ECU_TABLE_USER_CFG_IFC_DISPLAY                          368 /*瞬时油耗显示形式*/
#define ECU_TABLE_USER_CFG_IFC_MAX                              369 /*瞬时油耗显示最大值*/
#define ECU_TABLE_USER_CFG_IFC_INTERVAL                         370 /*瞬时油耗取值间隔*/
#define ECU_TABLE_USER_PLG_KEEP_TIME_HIGH                       371 /*电动尾门静止时间配置高8位*/
#define ECU_TABLE_USER_PLG_KEEP_TIME_LOW                        372 /*电动尾门静止时间配置低8位*/
#define ECU_TABLE_USER_VOLCANIC_APP                             373 /*Volcanic APP*/
#define ECU_TABLE_USER_SECOND_ROW_HEAT                          374 /*Second row seat heating*/
#define ECU_TABLE_USER_SECOND_ROW_VENT                          375 /*Second row seat ventilation*/
#define ECU_TABLE_USER_REAR_BUMPER_TYPE                         376 /*Rear Bumper Type*/
#define ECU_TABLE_USER_MIRROR_SCROLL_DOWN                       377 /*Rearview Mirror Scroll down*/
#define ECU_TABLE_USER_LEARN_SK                                 378 /*Four tone speech recognition*/
#define ECU_TABLE_USER_ASU                                      379 /*ASU*/
#define ECU_TABLE_USER_DRIVERSEAT_HEADREST                      380 /*主驾座椅坐头枕形式*/
#define ECU_TABLE_USER_PASSENGERSEAT_RESET                      381 /*副驾座椅一键复位*/
#define ECU_TABLE_USER_HYDROGEN_CAP_SWITCH                      382 /*加氢盖*/
#define ECU_TABLE_USER_AMB                                      383 /*车内氛围灯*/
#define ECU_TABLE_USER_BRAKE_FLUID_LEVEL                        384 /*制动液位低信号*/
#define ECU_TABLE_USER_SIGNAL_SHIELD                            385 /*过检屏蔽（AEB/ACC/IACC）*/
#define ECU_TABLE_USER_PASSENGER_SCREEN                         386 /*副驾屏*/
#define ECU_TABLE_USER_ANC                                      387 /*主动降噪*/
#define ECU_TABLE_USER_MOTION_TRUNK                             388 /*体感行李箱*/
#define ECU_TABLE_USER_ZERO_GRAVITY_SEAT                        389 /*零重力座椅*/
#define ECU_TABLE_USER_REAR_PANEL                               390 /*后排面板*/
#define ECU_TABLE_USER_SCENE_BLOCKS                             391 /*场景积木*/
#define ECU_TABLE_USER_3D_VEHICLE_CONTROL                       392 /*3D车控*/
#define ECU_TABLE_USER_VISOR_CURTAIN                            393 /*遮阳帘*/
#define ECU_TABLE_USER_REAR_WIPER                               394 /*后雨刮*/
#define ECU_TABLE_USER_IC                                       395 /*仪表方案*/
#define ECU_TABLE_USER_E_AIROUTLET                              396 /*电动出风口*/
#define ECU_TABLE_USER_SMART_KEY                                397 /*智能遥控钥匙*/
#define ECU_TABLE_USER_AVAS_5W                                  398 /*AVAS-5W纯扬声器*/
#define ECU_TABLE_USER_PLG_DEGREE_OF_CHE_CONF                   399 /*电动尾门变化度数配置*/
#define ECU_TABLE_USER_ELECTRIC_DESK                            400 /*电动小桌板*/
#define ECU_TABLE_USER_HIGH_BEAM_ASSIST                         401 /*智能大灯(远近光自动切换)*/
#define ECU_TABLE_USER_INIT_FUEL_CONSUME                        402 /*Initial Fuel Consumption*/
#define ECU_TABLE_USER_LOCK_TONE                                403 /*离车闭锁音方式*/
#define ECU_TABLE_USER_SOUND_POSITIO                            404 /*Bit0:音场设置*/
#define ECU_TABLE_USER_GPS_SOURCE                               405 /*Bit3:GPS 信号来源*/
#define ECU_TABLE_USER_GEAR_SWITCH                              406 /*Bit5:换挡提示软开关*/
#define ECU_TABLE_USER_LOW_WARNING                              407 /*Bit6：低速提醒音软开关*/
#define ECU_TABLE_USER_ENERGY_FEEDBACK_STRENGTH                 408 /*Bit7：能量回馈强度设置开关 （0:无, 1:有）*/
#define ECU_TABLE_USER_NAVIGATION_PROJECTION                    409 /*Bit1:全液晶仪表导航投屏*/
#define ECU_TABLE_USER_CUSTOMIZATION_SETTING                    410 /*Bit2:个性化仪表*/
#define ECU_TABLE_USER_5G_FUNC                                  411 /*5G功能*/
#define ECU_TABLE_USER_VOICE_CTRL_WINDOW                        412 /*Bit0~1:语音控制车窗功能；*/
#define ECU_TABLE_USER_VOICE_CTRL_SUNROOF                       413 /*Bit2:语音控制天窗软开关和抽烟模式*/
#define ECU_TABLE_USER_EXTERNAL_LIGHT_WELCOME                   414 /*Bit4:灯光主动迎宾软开关*/
#define ECU_TABLE_USER_AUTO_WIPE_IN_REVERSE_GEAR                415 /*Bit5:倒挡后雨刮自动刮刷软开关*/
#define ECU_TABLE_USER_AUTO_CLOSE_WINDOW                        416 /*Bit6:下雨自动关窗软开关（雨量传感器）*/
#define ECU_TABLE_USER_TREAD_WELCOME                            417 /*Bit0:趋势迎宾软开关*/
#define ECU_TABLE_USER_CAR_SEARCH_MODE                          418 /*寻车模式设置*/
#define ECU_TABLE_USER_AUTO_VISOR_CURTAIN                       419 /*锁车遮阳帘关闭*/
#define ECU_TABLE_USER_LANE_CHANGE_LIGHTS                       420 /*变道灯次数设置*/
#define ECU_TABLE_USER_AR_PJT_TAILDOOR                          421 /*AR投影尾门软开关*/
#define ECU_TABLE_USER_ADAS                                     422 /*ADAS等级*/
#define ECU_TABLE_USER_SPAM                                     423 /*智能领航辅助系统*/
#define ECU_TABLE_USER_ISAM                                     424 /*智能限速辅助模式*/
#define ECU_TABLE_USER_AUTO_PILOT                               425 /*AutoPilot设置开关*/
#define ECU_TABLE_USER_AUTO_FUEL_SAVE                           426 /*“i驾趣”智能节油模式软开关*/
#define ECU_TABLE_USER_LAMP_LANG_CLASSIC                        427 /*灯语设置效果----经典*/
#define ECU_TABLE_USER_LAMP_LANG_PULSE                          428 /*灯语设置效果----脉动*/
#define ECU_TABLE_USER_LAMP_LANG_METEOR                         429 /*灯语设置效果----流星*/
#define ECU_TABLE_USER_LAMP_LANG_BRICK                          430 /*灯语设置效果----积木*/
#define ECU_TABLE_USER_TRANSMISSION                             431 /*变速箱类型*/
#define ECU_TABLE_USER_ENGINE_TYPE                              432 /*发动机类型*/
#define ECU_TABLE_USER_STT                                      433 /*STT*/
#define ECU_TABLE_USER_DMTR                                     434 /*DMTR*/
#define ECU_TABLE_USER_GATEWAY                                  435 /*网关*/
#define ECU_TABLE_USER_TBOX                                     436 /*TBOX*/
#define ECU_TABLE_USER_FRONT_FOG_LIGHT                          437 /*前雾灯*/
#define ECU_TABLE_USER_AFS                                      438 /*AFS*/
#define ECU_TABLE_USER_DOOR_OPEN_WARNING                        439 /*车门未关提醒*/
#define ECU_TABLE_USER_PASSENGER_BELT                           440 /*副驾驶安全带未系提醒*/
#define ECU_TABLE_USER_MAINTAIN_WARNING                         441 /*保养提醒*/
#define ECU_TABLE_USER_ECONOMIC_MODE                            442 /*经济模式*/
#define ECU_TABLE_USER_SPORT_MODE                               443 /*运动模式*/
#define ECU_TABLE_USER_SNOWFLAKE_PATTERN                        444 /*雪花模式*/
#define ECU_TABLE_USER_ENGINE_STANDARD                          445 /*发动机标准*/
#define ECU_TABLE_USER_ILDW                                     446 /*LDW*/
#define ECU_TABLE_USER_ILKA                                     447 /*LKA*/
#define ECU_TABLE_USER_IABS_ESC                                 448 /*ABS/ESC*/
#define ECU_TABLE_USER_AUTOHOLD                                 449 /*AUTOHOLD*/
#define ECU_TABLE_USER_ELECTRONIC_SHIFT                         450 /*电子换挡*/
#define ECU_TABLE_USER_ITEST_DRIVE                              451 /*试驾显示；*/
#define ECU_TABLE_USER_AUTO_WIPER                               452 /*自动雨刮*/
#define ECU_TABLE_USER_POWER_MGR                                453 /*电源管理*/
#define ECU_TABLE_USER_IHBC                                     454 /*IHBC*/
#define ECU_TABLE_USER_OFFICIAL_FUEL_CONSUMPTIONH               455 /*官方油耗*/
#define ECU_TABLE_USER_OFFICIAL_FUEL_CONSUMPTIONL               456 /*官方油耗*/
#define ECU_TABLE_USER_AUTO_DRIVE_LOCK                          457 /*Bit3:行车自动落锁软开关*/
#define ECU_TABLE_USER_IFCW                                     458 /*Bit6:前碰撞预警软开关及灵敏度*/
#define ECU_TABLE_USER_ISTEEP_DESCENT                           459 /*Bit0:陡坡缓降*/
#define ECU_TABLE_USER_PHOTO_ALBUM                              460 /*Bit4：相机与相册APP*/
#define ECU_TABLE_USER_LOOK_AROUND                              461 /*Bit5：环视记录仪APP*/
#define ECU_TABLE_USER_ASD                                      462 /*Bit6：ASD主动声浪*/
#define ECU_TABLE_USER_RMIRROR                                  463 /*Bit0-1：后视镜（0：普通外后视镜（无自动折叠）；1-普通外后视镜（带自动折叠）；2-电子外后视镜）*/
#define ECU_TABLE_USER_STARRY_SKY_MODE                          464 /*Bit3：星空模式*/
#define ECU_TABLE_USER_REFRESHING                               465 /*Bit4：提神模式*/
#define ECU_TABLE_USER_LIGHT_SHOW                               466 /*Bit6：灯语/灯光秀/say Hi*/
#define ECU_TABLE_USER_AR_ATMOSPHERE_LAMP                       467 /*Bit7：VPA氛围灯*/
#define ECU_TABLE_USER_A_LAMP                                   468 /*Bit0：A字灯*/
#define ECU_TABLE_USER_FOD                                      469 /*Bit1：前方障碍检测软开关*/
#define ECU_TABLE_USER_LOD                                      470 /*Bit2：侧方障碍检测软开关*/
#define ECU_TABLE_USER_FOUR_WHEEL_DRIVE                         471 /*四驱*/
#define ECU_TABLE_USER_E4WWD                                    472 /*电动4向腰托*/
#define ECU_TABLE_USER_CONFORTABLE_PARKING                      473 /*舒适停车软开关*/
#define ECU_TABLE_USER_AUTO_PARKING                             474 /*自动驻车软开关*/
#define ECU_TABLE_USER_TRACTION_MODE                            475 /*牵引模式软开关*/
#define ECU_TABLE_USER_NIGHT_EYE                                476 /*夜视功能*/
#define ECU_TABLE_USER_WHUD                                     477 /*WHUD设置*/
#define ECU_TABLE_USER_MUSICAL_RHYTHM                           478 /*音乐律动设置*/
#define ECU_TABLE_USER_MAIN_DRIVER_AIRBAG                       479 /*主驾安全气囊软开关*/
#define ECU_TABLE_USER_PASSENGER_AIRBAG                         480 /*副驾安全气囊软开关*/
#define ECU_TABLE_USER_SIMULATE_SOUND                           481 /*模拟声浪*/
#define ECU_TABLE_USER_INTERNEL_LIGHT_WELCOME                   482 /*车内灯光迎宾*/
#define ECU_TABLE_USER_REAR_SUNROOF                             483 /*后排天窗配置*/
#define ECU_TABLE_USER_AIR_ANTI_FOG                             484 /*空调防起雾设置开关*/
#define ECU_TABLE_USER_STEERING_WELCOME                         485 /*方向盘迎宾与记忆*/
#define ECU_TABLE_USER_INITIATIVE_SUSPENSION                    486 /*主动悬架*/
#define ECU_TABLE_USER_SPEED_LIMIT_DEVIVATION                   487 /*限速偏差设定*/
#define ECU_TABLE_USER_WORKING_COND                             488 /*标准工况/实际工况的选项*/
#define ECU_TABLE_USER_CHILD_SEAT                               489 /*儿童座椅*/
#define ECU_TABLE_USER_VOICE_REGION                             490 /*音区*/
#define ECU_TABLE_USER_SOUND_WAVE                               491 /*超跑声浪*/
#define ECU_TABLE_USER_HUB_PACKAGE                              492 /*轮毂包*/
#define ECU_TABLE_USER_AUTO_PROJECTION_LAMP                     493 /*可随场景切换车侧投影灯*/
#define ECU_TABLE_USER_NON_EDITABLE_HEADLAMP                    494 /*不可编辑前投影大灯*/
#define ECU_TABLE_USER_EDITABLE_HEADLIGHT                       495 /*可自定义编辑后交互大灯*/
#define ECU_TABLE_USER_FLIP_ICM                                 496 /*8.8吋翻转仪表*/
#define ECU_TABLE_USER_SCISSORS_DOOR                            497 /*剪刀门*/
#define ECU_TABLE_USER_SMART_CAR_UPGRADE                        498 /*P2P智驾升级包*/
#define ECU_TABLE_USER_SEAT_WELCOME                             499 /*Bit6:座椅迎宾及记忆*/
#define ECU_TABLE_USER_SEAT_HEATING                             500 /*Bit0-1: 座椅加热*/
#define ECU_TABLE_USER_RADAR_SHOW                               501 /*Bit0-1: 雷达警示显示*/
#define ECU_TABLE_USER_NAVIGATION_MAP                           502 /*Navigation map*/
#define ECU_TABLE_USER_NUM_OF_USB_PORTS                         503 /*Number of USB Ports*/
#define ECU_TABLE_USER_PAB_TOUCH_SWITCH                         504 /*PAB Touch Switch*/
#define ECU_TABLE_USER_PASSENGER_SWITCH                         505 /*Passenger Frontal Airbag Switch */
#define ECU_TABLE_USER_DRIVING_POWER_TYPE                       506 /*Driving Power Type*/
#define ECU_TABLE_USER_RUDDER_TYPE                              507 /*Left and right rudder type*/
#define ECU_TABLE_USER_COMPASS_WORSHIP                          508 /*Compass Of Worship*/
#define ECU_TABLE_USER_E_DISCHARGE_FUNC                         509 /*External Discharge Function*/
#define ECU_TABLE_USER_COUNTRY_OR_REGION                        510 /*country or region*/
#define ECU_TABLE_USER_HEATING_GEAR                             511 /*Heating gear*/
#define ECU_TABLE_USER_VENTILATION_GEAR                         512 /*Ventilation gear*/
#define ECU_TABLE_USER_LIGHT_SENSOR_TYPE                        513 /*光线传感器类型*/
#define ECU_TABLE_USER_STEERING_MEM                             514 /*电动调节方向盘记忆*/
#define ECU_TABLE_USER_PASSENGERSEAT_MEMORY                     515 /*副驾座椅记忆*/
#define ECU_TABLE_USER_AUTO_FOG_REMOVAL                         516 /*自动除雾*/
#define ECU_TABLE_USER_CHILD_LOCK                               517 /*电子儿童锁*/
#define ECU_TABLE_USER_WIPER_NOZZLE_HEAT                        518 /*雨刮喷嘴加热*/
#define ECU_TABLE_USER_AIR_QUALITY_SYSTEM                       519 /*Air Quality System空气质量净化系统*/
#define ECU_TABLE_USER_SECOND_AC                                520 /*Second Row Air Conditioning Control二排独立空调控制*/
#define ECU_TABLE_USER_THREE_AC                                 521 /*Three Row Independent Air Conditioning三排独立空调*/
#define ECU_TABLE_USER_TWO_WAY_RUDDER                           522 /*Lefe/Right Rudder左右舵*/
#define ECU_TABLE_USER_NFC_KEY_NUM                              523 /*NFC钥匙数量*/
#define ECU_TABLE_USER_E0X_PLATFORM                             524 /*E0X平台*/
#define ECU_TABLE_USER_SUSPENSION_SPRING                        525 /*后悬架弹簧形式*/
#define ECU_TABLE_USER_CHASSIS_REDUNDANCY                       526 /*底盘冗余*/
#define ECU_TABLE_USER_LONG_LIDAR                               527 /*长距激光雷达*/
#define ECU_TABLE_USER_BLIND_LIDAR                              528 /*补盲激光雷达*/
#define ECU_TABLE_USER_FRONT_MILLMETER_RADER                    529 /*前毫米波雷达*/
#define ECU_TABLE_USER_TIRE_SPEC                                530 /*轮胎规格*/
#define ECU_TABLE_USER_ANGULAR_MILLMETER_RADER                  531 /*角毫米波雷达*/
#define ECU_TABLE_USER_AAC                                      532 /*周视摄像头*/
#define ECU_TABLE_USER_RCM                                      533 /*RCM*/
#define ECU_TABLE_USER_FWC                                      534 /*前视广摄像头*/
#define ECU_TABLE_USER_FLC                                      535 /*前视长焦摄像头*/
#define ECU_TABLE_USER_FAC                                      536 /*前视智能摄像头*/
#define ECU_TABLE_USER_AUTOPILOT                                537 /*自动驾驶控制中心*/
#define ECU_TABLE_USER_HIGHPRECISION_MODULE                     538 /*高精定位模块*/
#define ECU_TABLE_USER_HEADREST_SPEAKER                         539 /*头枕扬声器*/
#define ECU_TABLE_USER_SEATS_NUM                                540 /*座椅数量*/
#define ECU_TABLE_USER_STEERING_STRING_ADJUST                   541 /*转向管柱调节*/
#define ECU_TABLE_USER_GROUND_LAMP                              542 /*照地灯*/
#define ECU_TABLE_USER_REAR_WINDSHIELD_HEAT                     543 /*后风挡玻璃加热功能*/
#define ECU_TABLE_USER_SUBWOOFER_NUM                            544 /*低音扬声器数量*/
#define ECU_TABLE_USER_H_SUBWOOFER_NUM                          545 /*重低音扬声器数量*/
#define ECU_TABLE_USER_TWEETER_NUM                              546 /*高音扬声器数量*/
#define ECU_TABLE_USER_ALTO_SPEAKER_NUM                         547 /*中音扬声器数量*/
#define ECU_TABLE_USER_SURROUND_SPEAKER_NUM                     548 /*环绕扬声器数量*/
#define ECU_TABLE_USER_FIRST_MAINTAIN_KILOMETER                 549 /*保养公里(首保)*/
#define ECU_TABLE_USER_INTERVAL_MAINTAIN_KILOMETER              550 /*保养公里(保养间隔)*/
#define ECU_TABLE_USER_VOLTAGE_OUTPUT                           551 /*220V电压输出*/
#define ECU_TABLE_USER_PASSENGER_MONITOR                        552 /*乘员监测*/
#define ECU_TABLE_USER_SPEED_LIMIT_SETTING                      553 /*组合仪表带限速设置*/
#define ECU_TABLE_USER_ERMIL                                    554 /*外后视镜镜片调节方式*/
#define ECU_TABLE_USER_VETC                                     555 /*车载电子收费单元*/
#define ECU_TABLE_USER_ERM_HEAT                                 556 /*外后视镜电加热功能*/
#define ECU_TABLE_USER_EAIRM                                    557 /*电动防眩目内后视镜*/
#define ECU_TABLE_USER_WASHING_LIQUID_LEVEL                     558 /*洗涤液位传感器*/
#define ECU_TABLE_USER_STEER_MODE                               559 /*转向模式选择*/
#define ECU_TABLE_USER_NAVIGATION                               560 /*导航信息*/
#define ECU_TABLE_USER_RADIO_ANT_PAR                            561 /*收音天线参数*/
#define ECU_TABLE_USER_UWB_KEY                                  562 /*UWB实体钥匙*/
#define ECU_TABLE_USER_USB_NUM                                  563 /*USB接口数量*/
#define ECU_TABLE_USER_SPEECH_RECOGNITION                       564 /*语音识别*/
#define ECU_TABLE_USER_DRIVERSEAT_WAIST_ADJUST                  565 /*驾驶员座椅腰部调节*/
#define ECU_TABLE_USER_PASSENGERSEAT_ADJUST_KEY                 566 /*副驾座椅调节老板键*/
#define ECU_TABLE_USER_PASSENGERSEAT_WAIST_ADJUST               567 /*副驾座椅腰部调节*/
#define ECU_TABLE_USER_REARSEAT_BACKREST_ADJUST                 568 /*二排座椅靠背调节*/
#define ECU_TABLE_USER_REARSEAT_CUSHION                         569 /*二排坐垫调节*/
#define ECU_TABLE_USER_REARSEAT_LEFT_WAIST_ADJUST               570 /*二排左座椅腰部调节*/
#define ECU_TABLE_USER_REARSEAT_RIGHT_WAIST_ADJUST              571 /*二排右座椅腰部调节*/
#define ECU_TABLE_USER_RAINFALL_SENSOR                          572 /*雨量传感器灵敏度软开关*/
#define ECU_TABLE_USER_DAB                                      573 /*DAB*/
#define ECU_TABLE_USER_MULTICOLOR_AMB                           574 /*多色车内氛围灯*/
#define ECU_TABLE_USER_LAMP_DELAY_OFF                           575 /*大灯延时关闭*/
#define ECU_TABLE_USER_INTERACTIVE_SIGNLE_LAMP                  576 /*交互式信号显示灯*/
#define ECU_TABLE_USER_LIGHT_WELCOME                            577 /*迎宾仪式点亮功能*/
#define ECU_TABLE_USER_FOUR_ZONE                                578 /*四音区*/
#define ECU_TABLE_USER_HICAR                                    579 /*Hicar*/
#define ECU_TABLE_USER_DRIVING_COMPUTER                         580 /*行车电脑*/
#define ECU_TABLE_USER_DISPLAY_DIMENSIONS                       581 /*音响及娱乐显示屏尺寸*/
#define ECU_TABLE_USER_WIFI                                     582 /*WIFI*/
#define ECU_TABLE_USER_BT                                       583 /*蓝牙功能*/
#define ECU_TABLE_USER_TELEMATICS_ANT                           584 /*Telematics天线*/
#define ECU_TABLE_USER_BRIGHTNESS_AUTO_ADJUST                   585 /*组合仪表亮度自动调节*/
#define ECU_TABLE_USER_REMOTE_CTRL                              586 /*手机APP远程控制*/
#define ECU_TABLE_USER_LION_INTELLIGENT_SYSTEM                  587 /*Lion人工智能系统*/
#define ECU_TABLE_USER_HAND_LEAVE_STEERING                      588 /*方向盘离手监测*/
#define ECU_TABLE_USER_STEERINGWHEEL_TURN_PAGA                  589 /*方向盘带仪表翻页*/
#define ECU_TABLE_USER_STEERINGWHEEL_MOREFUNC_KEY               590 /*多功能方向盘按键*/
#define ECU_TABLE_USER_ICM_SIZE                                 591 /*组合仪表尺寸*/
#define ECU_TABLE_USER_PRAS                                     592 /*泊车雷达辅助系统*/
#define ECU_TABLE_USER_DFM                                      593 /*DFM驾驶员优先模式*/
#define ECU_TABLE_USER_AUTO_LAMP_CTRL                           594 /*智能大灯控制*/
#define ECU_TABLE_USER_PPMID                                    595 /*PPMID*/
#define ECU_TABLE_USER_FLDRM                                    596 /*FLDRM*/
#define ECU_TABLE_USER_ELECTRIC_TAIL                            597 /*电动尾翼*/
#define ECU_TABLE_USER_REARSEAT_MEMORY                          598 /*二排座椅记忆*/
#define ECU_TABLE_USER_MIRROR_TURN_DOWN                         599 /*后视镜倒车下翻*/
#define ECU_TABLE_USER_DRIVING_FORM                             600 /*驱动形式*/
#define ECU_TABLE_USER_FORCE_LIMITING_SEATBELT                  601 /*副驾驶员双限力式安全带*/
#define ECU_TABLE_USER_ELECTRIC_REAR_SPOILER                    602 /*电动后扰流板*/
#define ECU_TABLE_USER_ZERO_G_SEAT_POSITION                     603 /*零重力座椅位置*/
#define ECU_TABLE_USER_RC                                       604 /*后视摄像头*/
#define ECU_TABLE_USER_SUBICM_SLIDING_FUNC                      605 /*副仪表板滑动功能*/
#define ECU_TABLE_USER_VEHICLE_TYPE                             606 /*项目配置*/
#define ECU_TABLE_USER_IPB                                      607 /*IPB*/
#define ECU_TABLE_USER_IDLE_START_STOP_TYPE                     608 /*IDLE_START_STOP_TYPE*/
#define ECU_TABLE_USER_IHU_BRAND                                609 /*BRAND*/
#define ECU_TABLE_USER_FUEL_CONSUMPTION_UNIT                    610 /*Unit of fuel consumption*/
#define ECU_TABLE_USER_TIRE_PRESSURE_UNIT                       611 /*Unit of tire pressure*/
#define ECU_TABLE_USER_GRAR_SHIFT                               612 /*Electronic Gear Shift Structure*/
#define ECU_TABLE_USER_TRANSMISSION_TYPE                        613 /*Transmission type 2*/
#define ECU_TABLE_USER_CONTINUOUS_DAMPING_CTRL                  614 /*CDC可调阻尼悬架*/
#define ECU_TABLE_USER_FLASH_GRILLE                             615 /*发光格栅*/
#define ECU_TABLE_USER_ICM_FRONE_RADAR                          616 /*Front Radar*/
#define ECU_TABLE_USER_FUEL_TANK_CAPACITY2                      617 /*fuel tank capacity2*/
#define ECU_TABLE_USER_PPMI                                     618 /*PPMI*/
#define ECU_TABLE_USER_ICM_IDLE_START_STOP_TYPE                 619 /*Idle start-stop type*/
#define ECU_TABLE_USER_FAPA_HIL                                 620 /*视频盒子内部配置字*/
#define ECU_TABLE_USER_C385_VEHICLE_TYPE                        621 /*C385系列车型类别*/
#define ECU_TABLE_USER_DVR_STORAGE_MEDIUM                       622 /*DVR存储方式*/



#define VEHICLE_CONFIG_MAX_LEN   128

typedef struct ecu_config_s
{
    uint8_t vehicle_config[VEHICLE_CONFIG_MAX_LEN];
}ecu_config_t;

typedef union ecu_func
{
    uint32_t idx;
    uint8_t result;
}ecu_func_t;

int ecu_config_init(void){return 1;}
int ecu_config_close(void){return 1;}

int ecu_config_set(ecu_config_t* ecu_config){return 1;}
int ecu_config_get(ecu_config_t* ecu_config){return 1;}

int ecu_config_get_func(uint32_t idx, uint8_t* result){return 1;}

int ecu_config_get_screen_param(void* data, int size){return 1;}
int ecu_config_set_screen_param(void* data, int size){return 1;}

int ecu_config_get_custom_flags(void* data, int size){return 1;}
int ecu_config_set_custom_flags(void* data, int size){return 1;}

int ecu_config_get_sysmon_flags(void){return 1;}
int ecu_config_set_sysmon_flags(bool set){return 1;}

#endif
/********************* (C) COPYRIGHT MEGA *******END OF FILE ********/
