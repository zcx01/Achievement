pragma Singleton
import QtQuick 2.0
QtObject {
//IACC使能开关(集成式自适应巡航、自动驾驶辅助)
property string t_TOPIC_ASSIST_HU_IACCENABLE                        :"assist/HU_IACCEnable"
//自动调整巡航车速使能请求(ICAR)
property string t_TOPIC_ASSIST_HU_CSLAENABLE                        :"assist/HU_CSLAEnable"
//超速报警声音提醒开关
property string t_TOPIC_ASSIST_HU_OVERSPEED_SOUND_WAR_ENABLE        :"assist/HU_OverspeedSoundWarEnable"
//LAS模式选择信号
property string t_TOPIC_ASSIST_HU_LASMODE_SELECTION                 :"assist/HU_LASModeSelection"
//LAS警告方式
property string t_TOPIC_ASSIST_HU_LASWARNING_MODE_SELECTION         :"assist/HU_LASWarningModeSelection"
//前碰撞预警设置
property string t_TOPIC_ASSIST_HU_FCWSETTING                        :"assist/HU_FCWSetting"
//前侧横向制动报警开关(ICAR)
property string t_TOPIC_ASSIST_HU_FCTAENABLE                        :"assist/HU_FCTAEnable"
//后侧横向预警开关(ICAR)
property string t_TOPIC_ASSIST_HU_RCTAENABLE                        :"assist/HU_RCTAEnable"
//后追尾预警使能
property string t_TOPIC_ASSIST_HU_RCWENABLE                         :"assist/HU_RCWEnable"
//自动制动使能开关
property string t_TOPIC_ASSIST_HU_AUTO_BRAKE_ENABLE                 :"assist/HU_AutoBrakeEnable"
//后侧横向制动开关
property string t_TOPIC_ASSIST_HU_RCTBENABLE                        :"assist/HU_RCTBEnable"
//前侧横向制动开关
property string t_TOPIC_ASSIST_HU_FCTBENABLE                        :"assist/HU_FCTBEnable"
//盲点检测/换道辅助设置
property string t_TOPIC_ASSIST_HU_BSDLCASETTING                     :"assist/HU_BSDLCASetting"
//紧急车道保持使能
property string t_TOPIC_ASSIST_HU_ELKENABLE                         :"assist/HU_ELKEnable"
//交通灯辅助使能
property string t_TOPIC_ASSIST_HU_TLAENABLE                         :"assist/HU_TLAEnable"
//开门预警开关
property string t_TOPIC_ASSIST_HU_SEAENABLE                         :"assist/HU_SEAEnable"
//语音警示开关
property string t_TOPIC_ASSIST_HU_AUDIO_WARNING_ENABLE              :"assist/HU_AudioWarningEnable"
//车门未关
property string t_TOPIC_ICCHIME_DOOR_OPEN_CHIME                     :"icchime/DoorOpenChime"
//档位切换
property string t_TOPIC_ICCHIME_GEAR_SHIFT_CHIME                    :"icchime/GearShiftChime"
//安全带未系
property string t_TOPIC_ICCHIME_SEAT_BELT_CHIME                     :"icchime/SeatBeltChime"
//ready提示音
property string t_TOPIC_ICCHIME_READY_CHIME                         :"icchime/ReadyChime"
//电源状态
property string t_TOPIC_ICDRIVING_POWER_STATUS                      :"icdriving/PowerStatus"
//车速
property string t_TOPIC_ICDRIVING_SPEED                             :"icdriving/Speed"
//动力电池百分比
property string t_TOPIC_ICDRIVING_POWER_BATTERY_PERCENT             :"icdriving/PowerBatteryPercent"
//油量百分比
property string t_TOPIC_ICDRIVING_OIL_PERCENT                       :"icdriving/OilPercent"
//电续航剩余里程
property string t_TOPIC_ICDRIVING_ELE_REMAIN_RANGE                  :"icdriving/EleRemainRange"
//油续航剩余里程
property string t_TOPIC_ICDRIVING_OIL_REMAIN_RANGE                  :"icdriving/OilRemainRange"
//档位
property string t_TOPIC_ICDRIVING_GEAR                              :"icdriving/Gear"
//驾驶模式
property string t_TOPIC_ICDRIVING_DRIVING_MODE                      :"icdriving/DrivingMode"
//瞬时功率 (驾驶能量)
property string t_TOPIC_ICDRIVING_ELECTRONIC_POWER                  :"icdriving/ElectronicPower"
//瞬时电耗
property string t_TOPIC_ICDRIVING_ELECTRONIC_CONSUME                :"icdriving/ElectronicConsume"
//电机转速
property string t_TOPIC_ICDRIVING_MOTOR_SPEED                       :"icdriving/MotorSpeed"
//能量流向
property string t_TOPIC_ICDRIVING_POWER_FLOW                        :"icdriving/PowerFlow"
//充电电压
property string t_TOPIC_ICDRIVING_CHARGE_VOLTAGE                    :"icdriving/ChargeVoltage"
//充电电流
property string t_TOPIC_ICDRIVING_CHARGE_CURRENT                    :"icdriving/ChargeCurrent"
//充电剩余时间（分钟）
property string t_TOPIC_ICDRIVING_CHARGE_REMAIN_TIME                :"icdriving/ChargeRemainTime"
//放电电压
property string t_TOPIC_ICDRIVING_DISCHARGE_VOLTAGE                 :"icdriving/DischargeVoltage"
//放电电流
property string t_TOPIC_ICDRIVING_DISCHARGE_CURRENT                 :"icdriving/DischargeCurrent"
//动力电池电压
property string t_TOPIC_ICDRIVING_HIGH_VOLT_BATTERY_VOLTAGE         :"icdriving/HighVoltBatteryVoltage"
//动力电池电流
property string t_TOPIC_ICDRIVING_HIGH_VOLT_BATTERY_CURRENT         :"icdriving/HighVoltBatteryCurrent"
//低压蓄电池电压
property string t_TOPIC_ICDRIVING_LOW_VOLT_BATTERY_VOLTAGE          :"icdriving/LowVoltBatteryVoltage"
//低压蓄电池电流
property string t_TOPIC_ICDRIVING_LOW_VOLT_BATTERY_CURRENT          :"icdriving/LowVoltBatteryCurrent"
//总行驶时间(不可清零 h)
property string t_TOPIC_ICDRIVING_TOTAL_DRIVE_TIME                  :"icdriving/TotalDriveTime"
//总行驶距离(不可清零 km)
property string t_TOPIC_ICDRIVING_TOTAL_DRIVE_DISTANCE              :"icdriving/TotalDriveDistance"
//累计行驶时间(h)
property string t_TOPIC_ICDRIVING_ACCUM_DRIVE_TIME                  :"icdriving/AccumDriveTime"
//累计行驶距离(km)
property string t_TOPIC_ICDRIVING_ACCUM_DRIVE_DISTANCE              :"icdriving/AccumDriveDistance"
//累计行驶平均车速（km/h）
property string t_TOPIC_ICDRIVING_ACCUM_AVG_SPEED                   :"icdriving/AccumAvgSpeed"
//累计平均电耗
property string t_TOPIC_ICDRIVING_ELE_ACCUM_AVG_CONSUME             :"icdriving/EleAccumAvgConsume"
//累计平均油耗
property string t_TOPIC_ICDRIVING_OIL_ACCUM_AVG_CONSUME             :"icdriving/OilAccumAvgConsume"
//自启动行驶时间(h)
property string t_TOPIC_ICDRIVING_CURRENT_DRV_TIME                  :"icdriving/CurrentDrvTime"
//自启动行驶距离(km)
property string t_TOPIC_ICDRIVING_CURRENT_DRV_DISTANCE              :"icdriving/CurrentDrvDistance"
//自启动行驶平均车速(km/h)
property string t_TOPIC_ICDRIVING_CURRENT_DRV_AVG_SPEED             :"icdriving/CurrentDrvAvgSpeed"
//自启动平均电耗
property string t_TOPIC_ICDRIVING_CURRENT_DRV_ELE_AVG_CONSUMPTION   :"icdriving/CurrentDrvEleAvgConsumption"
//自启动平均油耗
property string t_TOPIC_ICDRIVING_CURRENT_DRV_OIL_AVG_CONSUMPTION   :"icdriving/CurrentDrvOilAvgConsumption"
//剩余氢气量
property string t_TOPIC_ICDRIVING_HYDROGEN_SURPLUS                  :"icdriving/HydrogenSurplus"
//氢剩余里程
property string t_TOPIC_ICDRIVING_HYDROGEN_REMAIN_RANGE             :"icdriving/HydrogenRemainRange"
//左前轮胎胎压
property string t_TOPIC_ICDRIVING_LEFT_FRONT_TYRE_BAR               :"icdriving/LeftFrontTyreBar"
//左前轮胎胎温
property string t_TOPIC_ICDRIVING_LEFT_FRONT_TYRE_TEMPERATURE       :"icdriving/LeftFrontTyreTemperature"
//右前轮胎胎压
property string t_TOPIC_ICDRIVING_RIGHT_FRONT_TYRE_BAR              :"icdriving/RightFrontTyreBar"
//右前轮胎胎温
property string t_TOPIC_ICDRIVING_RIGHT_FRONT_TYRE_TEMPERATURE      :"icdriving/RightFrontTyreTemperature"
//左后轮胎胎压
property string t_TOPIC_ICDRIVING_LEFT_BACK_TYRE_BAR                :"icdriving/LeftBackTyreBar"
//左后轮胎胎温
property string t_TOPIC_ICDRIVING_LEFT_BACK_TYRE_TEMPERATURE        :"icdriving/LeftBackTyreTemperature"
//右后轮胎胎压
property string t_TOPIC_ICDRIVING_RIGHT_BACK_TYRE_BAR               :"icdriving/RightBackTyreBar"
//右后轮胎胎温
property string t_TOPIC_ICDRIVING_RIGHT_BACK_TYRE_TEMPERATURE       :"icdriving/RightBackTyreTemperature"
//ACC目标横向距离
property string t_TOPIC_ICDRIVING_ACCTARGET_LAT_RANGE               :"icdriving/ACCTargetLatRange"
//ACC目标车纵向距离
property string t_TOPIC_ICDRIVING_ACCTARGET_LNG_RANGE               :"icdriving/ACCTargetLngRange"
//AEB目标横向距离
property string t_TOPIC_ICDRIVING_AEBTARGET_LAT_RANGE               :"icdriving/AEBTargetLatRange"
//AEB目标纵向距离
property string t_TOPIC_ICDRIVING_AEBTARGET_LNG_RANGE               :"icdriving/AEBTargetLngRange"
//ACC跟车距离等级
property string t_TOPIC_ICDRIVING_DISTANCE_LEVEL                    :"icdriving/DistanceLevel"
//左车道前方目标1横向距离
property string t_TOPIC_ICDRIVING_FLTARGET1LAT_RANGE                :"icdriving/FLTarget1LatRange"
//左车道前方目标1纵向距离
property string t_TOPIC_ICDRIVING_FLTARGET1LNG_RANGE                :"icdriving/FLTarget1LngRange"
//左车道前方目标2横向距离
property string t_TOPIC_ICDRIVING_FLTARGET2LAT_RANGE                :"icdriving/FLTarget2LatRange"
//左车道前方目标2纵向距离
property string t_TOPIC_ICDRIVING_FLTARGET2LNG_RANGE                :"icdriving/FLTarget2LngRange"
//右车道前方目标1横向距离
property string t_TOPIC_ICDRIVING_FRTARGET1LAT_RANGE                :"icdriving/FRTarget1LatRange"
//右车道前方目标1纵向距离
property string t_TOPIC_ICDRIVING_FRTARGET1LNG_RANGE                :"icdriving/FRTarget1LngRange"
//右车道前方目标2横向距离
property string t_TOPIC_ICDRIVING_FRTARGET2LAT_RANGE                :"icdriving/FRTarget2LatRange"
//右车道前方目标2纵向距离
property string t_TOPIC_ICDRIVING_FRTARGET2LNG_RANGE                :"icdriving/FRTarget2LngRange"
//本车道行人目标1横向距离
property string t_TOPIC_ICDRIVING_HOST_PED_LAT_RANGE_1              :"icdriving/HostPedLatRange_1"
//本车道行人目标1纵向距离
property string t_TOPIC_ICDRIVING_HOST_PED_LNG_RANGE_1              :"icdriving/HostPedLngRange_1"
//本车道潜在目标横向距离
property string t_TOPIC_ICDRIVING_HOST_POTENTIAL_TARGET_LAT_RANGE   :"icdriving/HostPotentialTargetLatRange"
//本车道潜在目标纵向距离
property string t_TOPIC_ICDRIVING_HOST_POTENTIAL_TARGET_LNG_RANGE   :"icdriving/HostPotentialTargetLngRange"
//车辆中心到左侧车道线的距离
property string t_TOPIC_ICDRIVING_LLANE_DISTANCE_FUSION             :"icdriving/LLaneDistanceFusion"
//车辆中心到左左侧车道线的距离
property string t_TOPIC_ICDRIVING_LLLANE_DISTANCE                   :"icdriving/LLLaneDistance"
//车辆中心到右侧车道线的距离
property string t_TOPIC_ICDRIVING_RLANE_DISTANCE_FUSION             :"icdriving/RLaneDistanceFusion"
//车辆中心到右右侧车道线的距离
property string t_TOPIC_ICDRIVING_RRLANE_DISTANCE                   :"icdriving/RRLaneDistance"
//方向盘转向角度
property string t_TOPIC_ICDRIVING_EPS_SAS_STEER_AG                  :"icdriving/EpsSasSteerAg"
//10km平均剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_AVRG_RESI_MILG_IN10KM     :"icdriving/VcuVehAvrgResiMilgIn10km"
//25km平均剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_AVRG_RESI_MILG_IN25KM     :"icdriving/VcuVehAvrgResiMilgIn25km"
//50km平均剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_AVRG_RESI_MILG_IN50KM     :"icdriving/VcuVehAvrgResiMilgIn50km"
//10km瞬时剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_RESI_MILG_IN10KM          :"icdriving/VcuVehResiMilgIn10km"
//25km瞬时剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_RESI_MILG_IN25KM          :"icdriving/VcuVehResiMilgIn25km"
//30km瞬时剩余里程
property string t_TOPIC_ICDRIVING_VCU_VEH_RESI_MILG_IN50KM          :"icdriving/VcuVehResiMilgIn50km"
//工况平均能耗值
property string t_TOPIC_ICDRIVING_VCU_VEH_AVRG_EGY_CNSE             :"icdriving/VcuVehAvrgEgyCnse"
//充电增加里程
property string t_TOPIC_ICDRIVING_VCU_VEH_INCR_MILG                 :"icdriving/VcuVehIncrMilg"
//背门开度百分比
property string t_TOPIC_ICDRIVING_BCM_TR_DOOR_OPEN_DEG              :"icdriving/BcmTrDoorOpenDeg"
//燃油长期行驶距离(km)
property string t_TOPIC_ICDRIVING_LONG_OIL_DRIVE_DISTANCE           :"icdriving/longOilDriveDistance"
//纯电长期行驶距离(km)
property string t_TOPIC_ICDRIVING_LONG_BATTERY_DRIVE_DISTANCE       :"icdriving/longBatteryDriveDistance"
//燃油小计里程行驶(km)
property string t_TOPIC_ICDRIVING_SMALL_OIL_DRIVE_DISTANCE          :"icdriving/smallOilDriveDistance"
//纯电小计里程行驶距离(km)
property string t_TOPIC_ICDRIVING_SMALL_BATTERY_DRIVE_DISTANCE      :"icdriving/smallBatteryDriveDistance"
//燃油自启动后行驶距离(km)
property string t_TOPIC_ICDRIVING_START_OIL_DRIVE_DISTANCE          :"icdriving/startOilDriveDistance"
//纯电自启动后行驶距离(km)
property string t_TOPIC_ICDRIVING_START_BATTERY_DRIVE_DISTANCE      :"icdriving/startBatteryDriveDistance"
//燃油补能后行驶距离(km)
property string t_TOPIC_ICDRIVING_SUPPLY_OIL_DRIVE_DISTANCE         :"icdriving/supplyOilDriveDistance"
//纯电充电后行驶距离(km)
property string t_TOPIC_ICDRIVING_SUPPLY_BATTERY_DRIVE_DISTANCE     :"icdriving/supplyBatteryDriveDistance"
//燃油长期行驶时间(min)
property string t_TOPIC_ICDRIVING_LONG_OIL_DRIVE_TIME               :"icdriving/longOilDriveTime"
//纯电长期行驶时间(min)
property string t_TOPIC_ICDRIVING_LONG_BATTERY_DRIVE_TIME           :"icdriving/longBatteryDriveTime"
//燃油小计里程行驶(min)
property string t_TOPIC_ICDRIVING_SMALL_OIL_DRIVE_TIME              :"icdriving/smallOilDriveTime"
//纯电小计里程行驶时间(min)
property string t_TOPIC_ICDRIVING_SMALL_BATTERY_DRIVE_TIME          :"icdriving/smallBatteryDriveTime"
//燃油自启动后行驶时间(min)
property string t_TOPIC_ICDRIVING_START_OIL_DRIVE_TIME              :"icdriving/startOilDriveTime"
//纯电自启动后行驶时间(min)
property string t_TOPIC_ICDRIVING_START_BATTERY_DRIVE_TIME          :"icdriving/startBatteryDriveTime"
//燃油补能后行驶时间(min)
property string t_TOPIC_ICDRIVING_SUPPLY_OIL_DRIVE_TIME             :"icdriving/supplyOilDriveTime"
//纯电充电后行驶时间(min)
property string t_TOPIC_ICDRIVING_SUPPLY_BATTERY_DRIVE_TIME         :"icdriving/supplyBatteryDriveTime"
//长期平均油耗(L/100KM)
property string t_TOPIC_ICDRIVING_LONG_OIL_AVG_CONSUME              :"icdriving/longOilAvgConsume"
//小计里程平均油耗(L/100KM)
property string t_TOPIC_ICDRIVING_SMALL_OIL_AVG_CONSUME             :"icdriving/smallOilAvgConsume"
//补能后平均油耗(L/100KM)
property string t_TOPIC_ICDRIVING_SUPPLY_OIL_AVG_CONSUME            :"icdriving/supplyOilAvgConsume"
//驾驶循环内平均油耗(L/100KM)
property string t_TOPIC_ICDRIVING_CYCLE_OIL_AVG_CONSUME             :"icdriving/cycleOilAvgConsume"
//长期平均电耗(L/100KM)
property string t_TOPIC_ICDRIVING_LONG_BATTERY_AVG_CONSUME          :"icdriving/longBatteryAvgConsume"
//小计里程平均电耗(L/100KM)
property string t_TOPIC_ICDRIVING_SMALL_BATTERY_AVG_CONSUME         :"icdriving/smallBatteryAvgConsume"
//补能后平均电耗(L/100KM)
property string t_TOPIC_ICDRIVING_SUPPLY_BATTERY_AVG_CONSUME        :"icdriving/supplyBatteryAvgConsume"
//驾驶循环内平均电耗(L/100KM)
property string t_TOPIC_ICDRIVING_CYCLE_BATTERY_AVG_CONSUME         :"icdriving/cycleBatteryAvgConsume"
//车外温度
property string t_TOPIC_ICDRIVING_TMS_AC_ENVTL_T                    :"icdriving/TmsAcEnvtlT"
//动力电池SOC低指示灯
property string t_TOPIC_ICWARNING_BCU_BATT_SOC_UNDER_LAMP           :"icwarning/BcuBattSocUnderLamp"
//电子锁文字提示
property string t_TOPIC_ICWARNING_VCU_CHRG_LCK_INFO                 :"icwarning/VcuChrgLckInfo"
//DCAC文字提示
property string t_TOPIC_ICWARNING_VCU_DCACINFO                      :"icwarning/VcuDCACInfo"
//BCU文字提示需求
property string t_TOPIC_ICWARNING_BCU_TEXT_DISP_REQ                 :"icwarning/BcuTextDispReq"
//启动信息提示
property string t_TOPIC_ICWARNING_VCU_VEH_START_INFO                :"icwarning/VcuVehStartInfo"
//电池热失控状态
property string t_TOPIC_ICWARNING_BCU_THERM_RUNAWAY_STS             :"icwarning/BcuThermRunawaySts"
//EPB文字提示请求
property string t_TOPIC_ICWARNING_EPB_TEXT_DISP_REQ                 :"icwarning/EpbTextDispReq"
//IB警示信号
property string t_TOPIC_ICWARNING_IB_WRNG                           :"icwarning/IbWrng"
//车辆闭锁提示请求
property string t_TOPIC_ICWARNING_BCM_VEH_LCK_ALRM                  :"icwarning/BcmVehLckAlrm"
//剩余保养提醒
property string t_TOPIC_ICWARNING_TBOX_RESI_MAINTAIN_REM            :"icwarning/TboxResiMaintainRem"
//方向盘加热功能状态
property string t_TOPIC_ICWARNING_BCM_STEER_WHL_HEATG_FCT_STS       :"icwarning/BcmSteerWhlHeatgFctSts"
//智能钥匙电池状态
property string t_TOPIC_ICWARNING_PEPS_KEY_BATT_STS                 :"icwarning/PepsKeyBattSts"
//
property string t_TOPIC_ICWARNING_BRAKE_FLUID_IN_L                  :"icwarning/BrakeFluidInL"
//拖车模式激活状态
property string t_TOPIC_ICWARNING_VCU_TRLR_MOD_ACTV_STS             :"icwarning/VcuTrlrModActvSts"
//远程无钥匙驾驶授权请求
property string t_TOPIC_ICWARNING_TBOX_REM_DRV_WO_KEY_REQ           :"icwarning/TboxRemDrvWoKeyReq"
//方向盘转角有效
property string t_TOPIC_ICWARNING_EPS_SAS_STEER_AG                  :"icwarning/EpsSasSteerAg"
//驾驶疲劳报警请求
property string t_TOPIC_ICWARNING_CDC_DRVR_FATIGUE_WARN_REQ         :"icwarning/CdcDrvrFatigueWarnReq"
//车门状态
property string t_TOPIC_ICWARNING_DOOR_OPEN_STS                     :"icwarning/DoorOpenSts"
//多个车门状态
property string t_TOPIC_ICWARNING_MULTI_DOOR_OPEN_STS               :"icwarning/MultiDoorOpenSts"
//前排风量档位
property string t_TOPIC_VEHCTRL_STS_TMS_FRNT_WIND_LVL               :"vehctrlSts/TmsFrntWindLvl"
//前出风模式
property string t_TOPIC_VEHCTRL_STS_TMS_FRNT_BLOW_MOD               :"vehctrlSts/TmsFrntBlowMod"
//主驾温度值
property string t_TOPIC_VEHCTRL_STS_TMS_DRVR_AUT_T                  :"vehctrlSts/TmsDrvrAutT"
//副驾温度值
property string t_TOPIC_VEHCTRL_STS_TMS_PASS_AUT_T                  :"vehctrlSts/TmsPassAutT"
//空调工作状态
property string t_TOPIC_VEHCTRL_STS_TMS_AC_ON_OFF_STS               :"vehctrlSts/TmsAcOnOffSts"
//前除霜状态
property string t_TOPIC_VEHCTRL_STS_TMS_FRNT_DEFROSTER              :"vehctrlSts/TmsFrntDefroster"
//后除霜工作状态
property string t_TOPIC_VEHCTRL_STS_BCM_RE_DFRSTR_STS               :"vehctrlSts/BcmReDfrstrSts"
//循环模式状态
property string t_TOPIC_VEHCTRL_STS_TMS_CYC_MOD                     :"vehctrlSts/TmsCycMod"
//前排空调自动模式状态
property string t_TOPIC_VEHCTRL_STS_TMS_FR_AUT_STS                  :"vehctrlSts/TmsFrAutSts"
//最大制冷状态
property string t_TOPIC_VEHCTRL_STS_TMS_MAX_AC_STS                  :"vehctrlSts/TmsMaxAcSts"
//HEAT状态
property string t_TOPIC_VEHCTRL_STS_TMS_HEAT_STS                    :"vehctrlSts/TmsHeatSts"
//车灯状态: 0 关 1 位置灯 2 近光灯 3 自动大灯
property string t_TOPIC_VEHCTRL_STS_BCM_AUTO_HEAD_LI_SET_STS        :"vehctrlSts/BcmAutoHeadLiSetSts"
//后雾灯设置 0 OFF 1 ON
property string t_TOPIC_VEHCTRL_STS_BCM_RE_FOGLMP_STS               :"vehctrlSts/BcmReFoglmpSts"
//蠕行功能设置状态 0x1:ON 0x2:OFF
property string t_TOPIC_VEHCTRL_STS_VCU_CRP_FCT_STS                 :"vehctrlSts/VcuCrpFctSts"
//ESC功能设置 0 OFF 1 ON
property string t_TOPIC_VEHCTRL_STS_ESP_FCT_OPEN_STS                :"vehctrlSts/EspFctOpenSts"
//加速模式
property string t_TOPIC_VEHCTRL_STS_VCU_ACCR_MOD                    :"vehctrlSts/VcuAccrMod"
//能量回收模式
property string t_TOPIC_VEHCTRL_STS_VCU_ENY_RECYCL_MOD              :"vehctrlSts/VcuEnyRecyclMod"
//EPS助力模式反馈
property string t_TOPIC_VEHCTRL_STS_EPS_STEER_MOD_FB                :"vehctrlSts/EpsSteerModFb"
//制动踏板感模式设置
property string t_TOPIC_VEHCTRL_STS_IBBRK_PEDL_MOD_STS              :"vehctrlSts/IBBrkPedlModSts"
//解锁模式设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_UNLCK_DOOR_TYP_SET_STS      :"vehctrlSts/BcmUnlckDoorTypSetSts"
//自动速度落锁设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_AUT_SPD_LCK_SET_STS         :"vehctrlSts/BcmAutSpdLckSetSts"
//驻车自动解锁设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_VEH_PARKING_UNLCK_SET_STS   :"vehctrlSts/BcmVehParkingUnlckSetSts"
//闭锁关窗设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_LCK_AUTO_CLS_WIN_SET_STS    :"vehctrlSts/BcmLckAutoClsWinSetSts"
//感应解闭锁设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_INDUCTION_UNLCK_SET_STS     :"vehctrlSts/BcmInductionUnlckSetSts"
//后视镜自动折叠设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_MIRR_AUT_FOLD_SET_STS       :"vehctrlSts/BcmMirrAutFoldSetSts"
//后视镜倒车辅助设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_MIRROR_SET_STS              :"vehctrlSts/BcmMirrorSetSts"
//驾驶位保存设置
property string t_TOPIC_VEHCTRL_STS_DSM_DRVR_SEAT_INFO_SAVE_STS_FB  :"vehctrlSts/DsmDrvrSeatInfoSaveStsFb"
//驾驶位调用设置
property string t_TOPIC_VEHCTRL_STS_DSM_DRVR_SEAT_INFO_CALL_SIG_FB  :"vehctrlSts/DsmDrvrSeatInfoCallSigFb"
//HUD开关信号
property string t_TOPIC_VEHCTRL_STS_CDC_HUD_SWT_SET                 :"vehctrlSts/CdcHudSwtSet"
//HUD自动调节亮度信号
property string t_TOPIC_VEHCTRL_STS_CDC_HUD_LI_BRI_LVL_AUTO_SET     :"vehctrlSts/CdcHudLiBriLvlAutoSet"
//背景光调光等级
property string t_TOPIC_VEHCTRL_STS_BCM_DIMMER_LVL                  :"vehctrlSts/BcmDimmerLvl"
//拖车模式激活状态
property string t_TOPIC_VEHCTRL_STS_VCU_TRLR_MOD_ACTV_STS           :"vehctrlSts/VcuTrlrModActvSts"
//雨刮器状态
property string t_TOPIC_VEHCTRL_STS_BCM_WIPR_STS                    :"vehctrlSts/BcmWiprSts"
//预约充电状态
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_STS              :"vehctrlSts/TboxBokgChrgSts"
//预约充电模式
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_MODE             :"vehctrlSts/TboxBokgChrgMode"
//预约充电开始时间（小时）
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_STRT_TI_HR       :"vehctrlSts/TboxBokgChrgStrtTiHr"
//预约充电开始时间（分钟）
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_STRT_TI_MIN      :"vehctrlSts/TboxBokgChrgStrtTiMin"
//预约充电结束时间（小时）
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_STOP_TIT_HR      :"vehctrlSts/TboxBokgChrgStopTitHr"
//预约充电结束时间（分钟）
property string t_TOPIC_VEHCTRL_STS_TBOX_BOKG_CHRG_STOP_TI_MIN      :"vehctrlSts/TboxBokgChrgStopTiMin"
//充电SOC目标值
property string t_TOPIC_VEHCTRL_STS_TBOX_SOC_CHRG_TAR_SET           :"vehctrlSts/TboxSocChrgTarSet"
//电池充电模式
property string t_TOPIC_VEHCTRL_STS_BCU_CHRG_MOD                    :"vehctrlSts/BcuChrgMod"
//充电锁自动解锁功能设置状态
property string t_TOPIC_VEHCTRL_STS_VCU_CHRG_AUTO_UNLCK_SET_STS_FB  :"vehctrlSts/VcuChrgAutoUnlckSetStsFb"
//定时通风开启模式
property string t_TOPIC_VEHCTRL_STS_TMS_AC_VENTN_ON_MOD             :"vehctrlSts/TmsAcVentnOnMod"
//钥匙长按通风设置状态
property string t_TOPIC_VEHCTRL_STS_TMS_AUTOWIND_SET2STS            :"vehctrlSts/TmsAutowindSet2Sts"
//钥匙开锁通风设置状态
property string t_TOPIC_VEHCTRL_STS_TMS_AUTOWIND_SET1STS            :"vehctrlSts/TmsAutowindSet1Sts"
//空调自干燥功能状态
property string t_TOPIC_VEHCTRL_STS_TMS_AUT_WIND_WORK_STS           :"vehctrlSts/TmsAutWindWorkSts"
//能量管理模式反馈
property string t_TOPIC_VEHCTRL_STS_VCU_ENY_MAGT_MOD                :"vehctrlSts/VcuEnyMagtMod"
//交流放电截止 SOC 反馈
property string t_TOPIC_VEHCTRL_STS_VCU_DCHA_SOC_LIMIT_VAL          :"vehctrlSts/VcuDchaSocLimitVal"
//充电舱盖开闭状态
property string t_TOPIC_VEHCTRL_STS_BCM_CHRG_HOOD_STS               :"vehctrlSts/BcmChrgHoodSts"
//能量距离选项状态
property string t_TOPIC_VEHCTRL_STS_ENERGYG_DIST_STS                :"vehctrlSts/EnergygDistSts"
//能耗选项设置反馈
property string t_TOPIC_VEHCTRL_STS_VCU_VEH_EGY_CNSE_SELECT_CFM     :"vehctrlSts/VcuVehEgyCnseSelectCfm"
//后视镜折叠
property string t_TOPIC_VEHCTRL_STS_BCM_MIRR_LOCK_STS               :"vehctrlSts/BCM_MirrLockSts"
//大灯高度手动调节设置状态
property string t_TOPIC_VEHCTRL_STS_BCM_LI_HIGHT_MANU_SET_STS       :"vehctrlSts/BcmLiHightManuSetSts"
//顶灯DOOR档状态
property string t_TOPIC_VEHCTRL_STS_BCM_DOOR_LI_STS                 :"vehctrlSts/BcmDoorLiSts"
//后视镜记忆反馈
property string t_TOPIC_VEHCTRL_STS_BDC_MIRR_MEMST                  :"vehctrlSts/BdcMirrMEmst"
//座椅礼让设置反馈
property string t_TOPIC_VEHCTRL_STS_DSM_EASY_ENTRY_STS              :"vehctrlSts/DsmEasyEntrySts"
//主驾座椅加热状态
property string t_TOPIC_VEHCTRL_STS_DSM_DRVR_HEAT_STS               :"vehctrlSts/DsmDrvrHeatSts"
//副驾座椅加热状态
property string t_TOPIC_VEHCTRL_STS_DSM_PASS_HEAT_STS               :"vehctrlSts/DsmPassHeatSts"
//主驾座椅通风状态
property string t_TOPIC_VEHCTRL_STS_DSM_DRVR_VENTN_STS              :"vehctrlSts/DsmDrvrVentnSts"
//副驾座椅通风状态
property string t_TOPIC_VEHCTRL_STS_DSM_PASS_VENTN_STS              :"vehctrlSts/DsmPassVentnSts"
//蓝牙钥匙允许访问反馈状态
property string t_TOPIC_VEHCTRL_STS_BLE_LCK_ACS_ALLWD_STS           :"vehctrlSts/BleLckAcsAllwdSts"
//Epb状态
property string t_TOPIC_VEHCTRL_STS_EPB_STS                         :"vehctrlSts/EpbSts"
//双温区同步功能状态
property string t_TOPIC_VEHCTRL_STS_TMS_WORK_SPACE_SYNC_STS         :"vehctrlSts/TmsWorkSpaceSyncSts"
//离子发生器工作状态
property string t_TOPIC_VEHCTRL_STS_TMS_PLASMA_STS                  :"vehctrlSts/TmsPlasmaSts"
//行驶加热状态
property string t_TOPIC_VEHCTRL_STS_BCU_DRV_HEAT_SET_STS            :"vehctrlSts/BcuDrvHeatSetSts"
//即时加热剩余时间
property string t_TOPIC_VEHCTRL_STS_BCU_PLS_HEAT_TI_REM             :"vehctrlSts/BcuPlsHeatTiRem"
//即时加热状态反馈
property string t_TOPIC_VEHCTRL_STS_BCUBATT_PLS_HEAG_STS_FB         :"vehctrlSts/BCUBattPlsHeagStsFb"
//系统能量流
property string t_TOPIC_VEHCTRL_STS_VCU_SYS_EGY_FLOW                :"vehctrlSts/VcuSysEgyFlow"
//充电桩连接状态
property string t_TOPIC_VEHCTRL_STS_BLE_CHRG_PILE_CNCT_SET_STS      :"vehctrlSts/BleChrgPileCnctSetSts"
//蓝牙状态(暂定义为该Topic 后续根据实际逻辑进行修改)
property string t_TOPIC_VEHCTRL_STS_BLUE_TEE_CONN_STS               :"vehctrlSts/BlueTeeConnSts"
//交流枪状态
property string t_TOPIC_VEHCTRL_STS_AC_CHRG_CNCTR_STS               :"vehctrlSts/AcChrgCnctrSts"
//低速行人报警声音类型反馈
property string t_TOPIC_VEHCTRL_STS_LOW_SPEED_PED_ALARM_TYPE_STS    :"vehctrlSts/LowSpeedPedAlarmTypeSts"
//SayHi声音类型设置反馈
property string t_TOPIC_VEHCTRL_STS_SAY_HI_SOUND_TYPE_STS           :"vehctrlSts/SayHiSoundTypeSts"
//个性化提示音类型设置反馈
property string t_TOPIC_VEHCTRL_STS_PERSONALIZED_CUE_TONE_STS       :"vehctrlSts/PersonalizedCueToneSts"
//召唤声开关反馈
property string t_TOPIC_VEHCTRL_STS_CALLING_SOUND_STS               :"vehctrlSts/CallingSoundSts"
//召唤声风格反馈
property string t_TOPIC_VEHCTRL_STS_CALLING_TYPE_STS                :"vehctrlSts/CallingTypeSts"
//立体扬声器功能设置-播放当前媒体反馈
property string t_TOPIC_VEHCTRL_STS_PLAY_CURR_MEDIA_STS             :"vehctrlSts/PlayCurrMediaSts"
//道路救援呼叫状态
property string t_TOPIC_VEHCTRL_STS_TBOX_ROADSIDE_CALL_STS          :"vehctrlSts/TboxRoadsideCallSts"
//紧急救援呼叫状态
property string t_TOPIC_VEHCTRL_STS_TBOX_EMGY_CALL_STS              :"vehctrlSts/TboxEmgyCallSts"
//道路救援扬声器请求
property string t_TOPIC_VEHCTRL_STS_TBOX_ROADSIDE_SPEAKER_REQ       :"vehctrlSts/TboxRoadsideSpeakerReq"
//紧急救援扬声器请求
property string t_TOPIC_VEHCTRL_STS_TBOX_EMGY_SPK_REQ               :"vehctrlSts/TboxEmgySpkReq"
//收到电动出风模式反馈
property string t_TOPIC_VEHCTRL_STS_I_TMSAIR_OUT_MOD_FB             :"vehctrlSts/iTMSAirOutModFb"
//动画图标提示空气净化功能开启
property string t_TOPIC_VEHCTRL_STS_TMS_AIR_CLEAN_STS_REMIND        :"vehctrlSts/TmsAirCleanStsRemind"
//空气净化语音提示
property string t_TOPIC_VEHCTRL_STS_TMS_AIR_CLEAN_ACOUST_WARN       :"vehctrlSts/TmsAirCleanAcoustWarn"
//后排风量调节
property string t_TOPIC_VEHCTRL_STS_ITMS_BACKT_WIND_LVL_SET         :"vehctrlSts/ItmsBacktWindLvlSet"
//自动除霜除雾功能状态
property string t_TOPIC_VEHCTRL_STS_ITMS_AUTO_DEFRST_DEFOG_FCT_STS  :"vehctrlSts/ItmsAutoDefrstDefogFctSts"
//电池即时加热档位请求
property string t_TOPIC_VEHCTRL_STS_BCU_BATT_PLS_HEATG_GEAR_REQ     :"vehctrlSts/BcuBattPlsHeatgGearReq"
//充电桩蓝牙ID
property string t_TOPIC_VEHCTRL_STS_BLE_CHRG_PILE_ID                :"vehctrlSts/BleChrgPileID"
//ID连接状态
property string t_TOPIC_VEHCTRL_STS_BLE_CNCT_STS_ID                 :"vehctrlSts/BleCnctStsID"
//日间行车灯状态
property string t_TOPIC_VEHCTRL_STS_BCM_DRV_LI_SET_FB               :"vehctrlSts/BcmDrvLiSetFb"
//智能远光功能开启状态
property string t_TOPIC_VEHCTRL_STS_LAS_HMAENABLE_STATUS            :"vehctrlSts/LAS_HMAEnableStatus"
//行李箱门状态
property string t_TOPIC_VEHCTRL_STS_BCM_TR_DOOR_STS                 :"vehctrlSts/BcmTrDoorSts"
//背门开度设置反馈
property string t_TOPIC_VEHCTRL_STS_BCM_TR_DOOR_OPEN_DEG_ST_FB      :"vehctrlSts/BcmTrDoorOpenDegStFb"
//能量管理模式记忆设置状态
property string t_TOPIC_VEHCTRL_STS_CDC_ENY_MAGT_MOD_MEMSET_STS     :"vehctrlSts/CdcEnyMagtModMEmsetSts"
//电量保持目标SOC反馈
property string t_TOPIC_VEHCTRL_STS_VCU_SOC_HOLD_FB                 :"vehctrlSts/VcuSocHoldFb"
//制冷制热模式反馈
property string t_TOPIC_VEHCTRL_STS_ITMS_HOT_COLD_MOD_FB            :"vehctrlSts/ItmsHotColdModFb"
//自动调整巡航车速使能状态
property string t_TOPIC_VEHCTRL_STS_ACC_CSLAENABLE_STATUS           :"vehctrlSts/ACC_CSLAEnableStatus"
//超速预警提示音状态
property string t_TOPIC_VEHCTRL_STS_LAS_OVERSPEED_SOUND_WARNING_EN_ST:"vehctrlSts/LAS_OverspeedSoundWarningEnSt"
//前碰撞预警设置状态
property string t_TOPIC_VEHCTRL_STS_ACC_FCWSETTING_STATUS           :"vehctrlSts/ACC_FCWSettingStatus"
//后向横向预警使能状态(ICAR)
property string t_TOPIC_VEHCTRL_STS_LCDAR_RCTAENABLE_STATUS         :"vehctrlSts/LCDAR_RCTAEnableStatus"
//后追尾预警使能状态
property string t_TOPIC_VEHCTRL_STS_LCDAL_RCWENABLE_STATUS          :"vehctrlSts/LCDAL_RCWEnableStatus"
//AEB(自动制动)使能开关状态(ICAR)
property string t_TOPIC_VEHCTRL_STS_ACC_AEBENABLE                   :"vehctrlSts/ACC_AEBEnable"
//盲点检测/换道辅助使能状态(ICAR)
property string t_TOPIC_VEHCTRL_STS_LCDAR_BSD_LCAENABLE_STATUS      :"vehctrlSts/LCDAR_BSD_LCAEnableStatus"
//紧急车道保持开关状态(ICAR)
property string t_TOPIC_VEHCTRL_STS_ACC_ELKENABLE_STATUS            :"vehctrlSts/ACC_ELKEnableStatus"
//交通灯辅助系统开关状态
property string t_TOPIC_VEHCTRL_STS_LAS_TLAENABLE                   :"vehctrlSts/LAS_TLAEnable"
//开门预警使能状态
property string t_TOPIC_VEHCTRL_STS_LCDAL_SEAENABLE_STATUS          :"vehctrlSts/LCDAL_SEAEnableStatus"
//语音警示开关状态
property string t_TOPIC_VEHCTRL_STS_LCDAL_AUDIO_WARNING_ENABLE_STATUS:"vehctrlSts/LCDAL_AudioWarningEnableStatus"
//恒温座舱功能设定状态
property string t_TOPIC_VEHCTRL_STS_CDC_TH_COCKPIT_FCT_SET_STS      :"vehctrlSts/CdcThCockpitFctSetSts"
//离车位保存设置反馈
property string t_TOPIC_VEHCTRL_STS_DSM_PARK_SPACE_STORG            :"vehctrlSts/DsmParkSpaceStorg"
//近光灯反馈
property string t_TOPIC_VEHCTRL_STS_BCM_LO_BEAM_STS                 :"vehctrlSts/BcmLoBeamSts"
//主驾座椅水平向前调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_SLD_BACKW_SWT               :"vehctrlSts/DsmSldBackwSwt"
//主驾座椅水平向后调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_SLD_FWD_SWT                 :"vehctrlSts/DsmSldFwdSwt"
//主驾座椅靠背向前调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_BACK_FWD_SWT                :"vehctrlSts/DsmBackFwdSwt"
//主驾座椅靠背向后调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_BACK_BACKW_SWT              :"vehctrlSts/DsmBackBackwSwt"
//主驾座椅垂直向上调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_RE_UPWD_SWT                 :"vehctrlSts/DsmReUpwdSwt"
//主驾座椅垂直向下调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_RE_DWNWD_SWT                :"vehctrlSts/DsmReDwnwdSwt"
//主驾座椅前端向上调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_FRNT_UPW_SWT                :"vehctrlSts/DsmFrntUpwSwt"
//主驾座椅前端向下调节开关
property string t_TOPIC_VEHCTRL_STS_DSM_FRNT_DWNWD_SWT              :"vehctrlSts/DsmFrntDwnwdSwt"
//紧急救援回拨电话请求
property string t_TOPIC_VEHCTRL_STS_TBOX_EMGY_CALL_BACK_REQ         :"vehctrlSts/TboxEmgyCallBackReq"
//紧急救援语音提示请求
property string t_TOPIC_VEHCTRL_STS_TBOX_EMGY_ACOUST_WARN_REQ       :"vehctrlSts/TboxEmgyAcoustWarnReq"
//驾驶模式
property string t_TOPIC_VEHCTRL_DRIVING_MODE                        :"vehctrl/DrivingMode"
//能量管理模式
property string t_TOPIC_VEHCTRL_CDC_EGY_MAGT_MOD_REQ                :"vehctrl/CdcEgyMagtModReq"
//加速模式
property string t_TOPIC_VEHCTRL_CDC_ACCR_MOD_SET                    :"vehctrl/CdcAccrModSet"
//能量回收模式
property string t_TOPIC_VEHCTRL_CDC_EGY_RECYCLE_MOD_SET             :"vehctrl/CdcEgyRecycleModSet"
//电助力转向模式
property string t_TOPIC_VEHCTRL_CDC_STEER_MOD_SET                   :"vehctrl/CdcSteerModSet"
//制动助力模式
property string t_TOPIC_VEHCTRL_CDC_BRK_PEDL_MOD_SET                :"vehctrl/CdcBrkPedlModSet"
//蠕行功能设置
property string t_TOPIC_VEHCTRL_CDC_CRP_FCT_SET                     :"vehctrl/CdcCrpFctSet"
//ESP功能设置
property string t_TOPIC_VEHCTRL_CDC_ESP_FCT_SET                     :"vehctrl/CdcEspFctSet"
//停车自动解锁
property string t_TOPIC_VEHCTRL_CDC_VEH_PARKING_UNLCK_SET           :"vehctrl/CdcVehParkingUnlckSet"
//行车自动落锁
property string t_TOPIC_VEHCTRL_CDC_AUT_SPD_LCK_SET                 :"vehctrl/CdcAutSpdLckSet"
//离车闭锁自动关窗
property string t_TOPIC_VEHCTRL_CDC_LEAVE_CAR_AUT_CLOSE_WIN_SET     :"vehctrl/CdcLeaveCarAutCloseWinSet"
//锁车后视镜自动折叠
property string t_TOPIC_VEHCTRL_CDC_MIRR_AUT_FOLD_SET               :"vehctrl/CdcMirrAutFoldSet"
//车灯状态: 1 关 2 位置灯 3 近光灯 4 自动大灯
property string t_TOPIC_VEHCTRL_CDC_AUTO_HEAD_LI_SET                :"vehctrl/CdcAutoHeadLiSet"
//后雾灯
property string t_TOPIC_VEHCTRL_CDC_REAR_FOG_LMP_SET                :"vehctrl/CdcRearFogLmpSet"
//背光亮度
property string t_TOPIC_VEHCTRL_CDC_DIMMER_LVL_SET                  :"vehctrl/CdcDimmerLvlSet"
//车门解锁
property string t_TOPIC_VEHCTRL_CDC_VEH_PARKING_DOOR_TYP_SET        :"vehctrl/CdcVehParkingDoorTypSet"
//加油盖
property string t_TOPIC_VEHCTRL_CDC_TANK_DOOR_LCK_REQ               :"vehctrl/CdcTankDoorLckReq"
//后备箱
property string t_TOPIC_VEHCTRL_CAR_TRUNK                           :"vehctrl/CarTrunk"
//EPB(CDC电子手刹开关设置)
property string t_TOPIC_VEHCTRL_CDC_EPB_SWT_SET                     :"vehctrl/CdcEpbSwtSet"
//前排风量设定
property string t_TOPIC_VEHCTRL_CDC_FRNT_WIND_LVL_SET               :"vehctrl/CdcFrntWindLvlSet"
//前出风模式设定
property string t_TOPIC_VEHCTRL_CDC_FRNT_BLOW_MOD_SET               :"vehctrl/CdcFrntBlowModSet"
//主驾温度设定
property string t_TOPIC_VEHCTRL_CDC_DRVR_TSET                       :"vehctrl/CdcDrvrTSet"
//副驾温度设定
property string t_TOPIC_VEHCTRL_CDC_PASS_TSET                       :"vehctrl/CdcPassTSet"
//AC设定请求
property string t_TOPIC_VEHCTRL_CDC_AC_SET_REQ                      :"vehctrl/CdcAcSetReq"
//前除霜模式设定
property string t_TOPIC_VEHCTRL_CDC_FRNT_DEFROSTER_SET              :"vehctrl/CdcFrntDefrosterSet"
//后除霜模式设定
property string t_TOPIC_VEHCTRL_CDC_RE_DEFROSTER_SET                :"vehctrl/CdcReDefrosterSet"
//循环模式设定
property string t_TOPIC_VEHCTRL_CDC_CYC_MOD_SET                     :"vehctrl/CdcCycModSet"
//前排空调自动模式设定
property string t_TOPIC_VEHCTRL_CDC_FRNT_AUT_MOD_OPEN_SET           :"vehctrl/CdcFrntAutModOpenSet"
//前排空调关闭请求
property string t_TOPIC_VEHCTRL_CDC_FRONT_AC_OFF_SET                :"vehctrl/CdcFrontAcOffSet"
//最大制冷开启请求
property string t_TOPIC_VEHCTRL_CDC_AC_MAX_SET                      :"vehctrl/CdcAcMaxSet"
//HEAT设定请求
property string t_TOPIC_VEHCTRL_CDC_HEAT_SET_R                      :"vehctrl/CdcHeatSetR"
//本地预约充电状态
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_STS                   :"vehctrl/CdcBokgChrgSts"
//本地预约充电模式
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_MOD                   :"vehctrl/CdcBokgChrgMod"
//本地预约充电开始时间时
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_STRT_TI_HR            :"vehctrl/CdcBokgChrgStrtTiHr"
//本地预约充电开始时间分
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_STRT_TI_MIN           :"vehctrl/CdcBokgChrgStrtTiMin"
//本地预约充电结束时间时
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_STOP_TI_HR            :"vehctrl/CdcBokgChrgStopTiHr"
//本地预约充电结束时间分
property string t_TOPIC_VEHCTRL_CDC_BOKG_CHRG_STOP_TI_MIN           :"vehctrl/CdcBokgChrgStopTiMin"
//本地充电目标SOC设置
property string t_TOPIC_VEHCTRL_CDC_CHRG_SOC_SET                    :"vehctrl/CdcChrgSocSet"
//交流充电电流限值设定
property string t_TOPIC_VEHCTRL_CDC_AC_CHRG_ILIM_SET                :"vehctrl/CdcAcChrgILimSet"
//电池充电模式
property string t_TOPIC_VEHCTRL_BCU_CHRG_MOD                        :"vehctrl/BcuChrgMod"
//电锁自动解锁功能设置
property string t_TOPIC_VEHCTRL_CDC_VEH_CHRG_UNLCK_SET_REQ          :"vehctrl/CdcVehChrgUnlckSetReq"
//拖车模式
property string t_TOPIC_VEHCTRL_CDC_TRLR_MOD_SET                    :"vehctrl/CdcTrlrModSet"
//定时通风开启请求功能模式
property string t_TOPIC_VEHCTRL_CDC_VENTN_ON_SET                    :"vehctrl/CdcVentnOnSet"
//钥匙长按通风设置
property string t_TOPIC_VEHCTRL_CDC_AUTO_WIND_LONG_PRESS_SET        :"vehctrl/CdcAutoWindLongPressSet"
//钥匙开锁通风设置
property string t_TOPIC_VEHCTRL_CDC_AUTO_WIND_UNLOCK_SET            :"vehctrl/CdcAutoWindUnlockSet"
//空调自干燥功能设置请求
property string t_TOPIC_VEHCTRL_CDC_AUT_WIND_SET                    :"vehctrl/CdcAutWindSet"
//交流放电截止SOC设置请求
property string t_TOPIC_VEHCTRL_CDC_DCHA_SOC_LIMIT_SET              :"vehctrl/CdcDchaSocLimitSet"
//充电舱盖开闭设置
property string t_TOPIC_VEHCTRL_CDC_CHRG_SET_REQ                    :"vehctrl/CdcChrgSetReq"
//能量距离选项设置
property string t_TOPIC_VEHCTRL_CDC_ENG_DIST_SW                     :"vehctrl/CdcEngDistSw"
//能耗选项
property string t_TOPIC_VEHCTRL_CDC_VEH_EGY_CNSE_SELECT             :"vehctrl/CdcVehEgyCnseSelect"
//雨刮档位
property string t_TOPIC_VEHCTRL_CDC_WASHER_ST                       :"vehctrl/CdcWasherSt"
//后视镜倒车辅助
property string t_TOPIC_VEHCTRL_CDC_MIRR_SET_STS                    :"vehctrl/CdcMirrSetSts"
//后视镜折叠
property string t_TOPIC_VEHCTRL_CDC_RE_MIRR_FOLD_REQ                :"vehctrl/CdcReMirrFoldReq"
//大灯高度手动调节设置
property string t_TOPIC_VEHCTRL_CDC_LI_HIGHT_MANU_SET               :"vehctrl/CdcLiHightManuSet"
//顶灯DOOR档设置
property string t_TOPIC_VEHCTRL_CDC_DOOR_LI_SWT_SET                 :"vehctrl/CdcDoorLiSwtSet"
//感应解闭锁设置
property string t_TOPIC_VEHCTRL_CDC_INDUCTION_UNLCK_SET             :"vehctrl/CdcInductionUnlckSet"
//左右后视镜选择开关
property string t_TOPIC_VEHCTRL_CDC_LEFT_RIGHT_MIRROR_SET_STS       :"vehctrl/CdcLeftRightMirrorSetSts"
//后视镜记忆
property string t_TOPIC_VEHCTRL_CDC_MIRR_MEMST_REQ                  :"vehctrl/CdcMirrMEmstReq"
//座椅礼让设置
property string t_TOPIC_VEHCTRL_CDC_EASY_ENTRY_SET                  :"vehctrl/CdcEasyEntrySet"
//主驾加热设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_SEAT_HEAT_SET              :"vehctrl/CdcDrvrSeatHeatSet"
//副驾加热设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_HEAT_SET              :"vehctrl/CdcPassSeatHeatSet"
//主驾座椅通风请求
property string t_TOPIC_VEHCTRL_CDC_DRVR_SEAT_WIND_REQ              :"vehctrl/CdcDrvrSeatWindReq"
//副驾座椅通风请求
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_WIND_REQ              :"vehctrl/CdcPassSeatWindReq"
//蓝牙钥匙允许访问设置
property string t_TOPIC_VEHCTRL_CDC_BLU_LCK_ACS_ALLWD_SET           :"vehctrl/CdcBluLckAcsAllwdSet"
//温区设定同步请求
property string t_TOPIC_VEHCTRL_CDC_WORK_SPACE_SET                  :"vehctrl/CdcWorkSpaceSet"
//离子发生器控制请求
property string t_TOPIC_VEHCTRL_CDC_PLASMA_OPEN_SET                 :"vehctrl/CdcPlasmaOpenSet"
//主动拨打道路救援电话
property string t_TOPIC_VEHCTRL_CDC_ROADSIDE_ASSC_STS               :"vehctrl/CdcRoadsideAsscSts"
//挂断道路救援电话
property string t_TOPIC_VEHCTRL_CDC_ROADSIDE_ASSC_CNCL_STS          :"vehctrl/CdcRoadsideAsscCnclSts"
//雨刮维修模式
property string t_TOPIC_VEHCTRL_CDC_WIPR_SRV_SIG                    :"vehctrl/CdcWiprSrvSig"
//主动拨打紧急救援
property string t_TOPIC_VEHCTRL_CDC_EMGY_ASSC_SET                   :"vehctrl/CdcEmgyAsscSet"
//行驶加热
property string t_TOPIC_VEHCTRL_CDC_DRV_HEAT_SET_REQ                :"vehctrl/CdcDrvHeatSetReq"
//即时加热
property string t_TOPIC_VEHCTRL_CDC_BATT_PLS_HEATG_SET              :"vehctrl/CdcBattPlsHeatgSet"
//行驶信息设置
property string t_TOPIC_VEHCTRL_DRV_INFO_SET                        :"vehctrl/DrvInfoSet"
//长期行驶信息复位设置
property string t_TOPIC_VEHCTRL_CDC_LONG_DRV_INFO_RST               :"vehctrl/CdcLongDrvInfoRst"
//小计里程行驶信息复位
property string t_TOPIC_VEHCTRL_CDC_SMALL_MILG_RST                  :"vehctrl/CdcSmallMilgRst"
//充电桩连接设置
property string t_TOPIC_VEHCTRL_CDC_CHRG_PILE_CNCT_SET              :"vehctrl/CdcChrgPileCnctSet"
//蓝牙连接请求
property string t_TOPIC_VEHCTRL_CDC_BLE_CNCT_REQ                    :"vehctrl/CdcBleCnctReq"
//蓝牙断开请求
property string t_TOPIC_VEHCTRL_CDC_BLE_OFF_REQ                     :"vehctrl/CdcBleOffReq"
//蓝牙删除请求
property string t_TOPIC_VEHCTRL_CDC_BLE_DELETE_REQ                  :"vehctrl/CdcBleDeleteReq"
//HUD开关信号
property string t_TOPIC_VEHCTRL_CDC_HUD_SWT_SET                     :"vehctrl/CdcHudSwtSet"
//HUD手动调节亮度
property string t_TOPIC_VEHCTRL_CDC_HUD_LI_BRI_LVL_SET              :"vehctrl/CdcHudLiBriLvlSet"
//HUD自动调节亮度
property string t_TOPIC_VEHCTRL_CDC_HUD_LI_BRI_LVL_AUTO_SET         :"vehctrl/CdcHudLiBriLvlAutoSet"
//HUD高度设置
property string t_TOPIC_VEHCTRL_CDC_HUD_HI_LVL_SET                  :"vehctrl/CdcHudHiLvlSet"
//HUD主题设置
property string t_TOPIC_VEHCTRL_CDC_HUD_THEME_SET                   :"vehctrl/CdcHudThemeSet"
//HUD显示模式设置
property string t_TOPIC_VEHCTRL_CDC_HUD_DISP_MODE_SET               :"vehctrl/CdcHudDispModeSet"
//低速行人报警开关
property string t_TOPIC_VEHCTRL_LOW_SPEED_PED_ALARM                 :"vehctrl/LowSpeedPedAlarm"
//低速行人报警声音类型
property string t_TOPIC_VEHCTRL_LOW_SPEED_PED_ALARM_TYPE            :"vehctrl/LowSpeedPedAlarmType"
//随速音量设置
property string t_TOPIC_VEHCTRL_VOLUME_WITH_SPEED                   :"vehctrl/VolumeWithSpeed"
//SayHi声音类型设置
property string t_TOPIC_VEHCTRL_SAY_HI_SOUND_TYPE                   :"vehctrl/SayHiSoundType"
//个性化提示音类型设置
property string t_TOPIC_VEHCTRL_PERSONALIZED_CUE_TONE               :"vehctrl/PersonalizedCueTone"
//召唤声开关
property string t_TOPIC_VEHCTRL_CALLING_SOUND                       :"vehctrl/CallingSound"
//召唤声风格
property string t_TOPIC_VEHCTRL_CALLING_TYPE                        :"vehctrl/CallingType"
//立体扬声器功能设置-播放当前媒体
property string t_TOPIC_VEHCTRL_PLAY_CURR_MEDIA                     :"vehctrl/PlayCurrMedia"
//前排空调运行请求 
property string t_TOPIC_VEHCTRL_CDC_FRNT_AC_RUNNG_REQ               :"vehctrl/CdcFrntAcRunngReq"
//用户操作自动出风模式
property string t_TOPIC_VEHCTRL_CDC_AIR_OUT_MOD_REQ                 :"vehctrl/CdcAirOutModReq"
//出风口1开闭请求
property string t_TOPIC_VEHCTRL_CDC_AIR_OUT_SWT_REQ1                :"vehctrl/CdcAirOutSwtReq1"
//出风口2开闭请求
property string t_TOPIC_VEHCTRL_CDC_AIR_OUT_SWT_REQ2                :"vehctrl/CdcAirOutSwtReq2"
//出风口3开闭请求
property string t_TOPIC_VEHCTRL_CDC_AIR_OUT_SWT_REQ3                :"vehctrl/CdcAirOutSwtReq3"
//出风口4开闭请求
property string t_TOPIC_VEHCTRL_CDC_AIR_OUT_SWT_REQ4                :"vehctrl/CdcAirOutSwtReq4"
//后排风量设定请求
property string t_TOPIC_VEHCTRL_CDC_BACKT_WIND_LVL_SET_REQ          :"vehctrl/CdcBacktWindLvlSetReq"
//自动除霜除雾设定请求信号
property string t_TOPIC_VEHCTRL_CDC_AUTO_DEFRST_DEFOG_STS_REQ       :"vehctrl/CdcAutoDefrstDefogStsReq"
//日间行车灯设置请求
property string t_TOPIC_VEHCTRL_CDC_DRV_LI_SET_REQ                  :"vehctrl/CdcDrvLiSetReq"
//小憩模式工作状态
property string t_TOPIC_VEHCTRL_CDC_RESPITE_MOD_STS                 :"vehctrl/CdcRespiteModSts"
//露营模式设置
property string t_TOPIC_VEHCTRL_CDC_CAMP_MOD_SET                    :"vehctrl/CdcCampModSet"
//智能远光功能开启
property string t_TOPIC_VEHCTRL_HU_HMAENABLE                        :"vehctrl/HU_HMAEnable"
//中控背门开闭请求
property string t_TOPIC_VEHCTRL_CDC_TR_DOOR_OPEN_REQ                :"vehctrl/CdcTrDoorOpenReq"
//背门开度设置请求
property string t_TOPIC_VEHCTRL_CDC_TR_DOOR_OPEN_DEG_REQ            :"vehctrl/CdcTrDoorOpenDegReq"
//电量保持目标SOC请求
property string t_TOPIC_VEHCTRL_CDC_SOC_HOLD_REQ                    :"vehctrl/CdcSocHoldReq"
//能量管理模式记忆设置请求
property string t_TOPIC_VEHCTRL_CDC_ENY_MAGT_MOD_MEMSET_REQ         :"vehctrl/CdcEnyMagtModMEmsetReq"
//制冷制热模式设定请求
property string t_TOPIC_VEHCTRL_CDC_HOT_COLD_MOD_ST_REQ             :"vehctrl/CdcHotColdModStReq"
//语音控制车窗
property string t_TOPIC_VEHCTRL_CDC_ACOUST_CTR_RIGHT_REAR_WINDOW    :"vehctrl/CdcAcoustCtrRightRearWindow"
//语音控制右前车窗
property string t_TOPIC_VEHCTRL_CDC_ACOUST_CTR_PASSENGER_WINDOW     :"vehctrl/CdcAcoustCtrPassengerWindow"
//语音控制左后车窗
property string t_TOPIC_VEHCTRL_CDC_ACOUST_CTR_LEFT_REAR_WINDOW     :"vehctrl/CdcAcoustCtrLeftRearWindow"
//语音控制左前车窗
property string t_TOPIC_VEHCTRL_CDC_ACOUST_CTR_DRIVER_WINDOW        :"vehctrl/CdcAcoustCtrDriverWindow"
//HUD视频设置
property string t_TOPIC_VEHCTRL_CDC_HUD_VIDEO_SET                   :"vehctrl/CdcHudVideoSet"
//驾驶位保存设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_SEAT_INFO_SAVE_SET         :"vehctrl/CdcDrvrSeatInfoSaveSet"
//副驾座椅靠背向后调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_BACK_BACK_ST          :"vehctrl/CdcPassSeatBackBackSt"
//副驾座椅靠背向前调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_BACK_FWD_ST           :"vehctrl/CdcPassSeatBackFwdSt"
//副驾座椅前端向下调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_FRNT_DWNWD_ST         :"vehctrl/CdcPassSeatFrntDwnwdSt"
//副驾座椅前端向上调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_FRNT_UPW_ST           :"vehctrl/CdcPassSeatFrntUpwSt"
//副驾座椅垂直向下调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_RE_DWNWD_ST           :"vehctrl/CdcPassSeatReDwnwdSt"
//副驾座椅垂直向上调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_RE_UPWD_ST            :"vehctrl/CdcPassSeatReUpwdSt"
//副驾座椅水平向前调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_SLD_BACKW_ST          :"vehctrl/CdcPassSeatSldBackwSt"
//副驾座椅水平向后调节设置
property string t_TOPIC_VEHCTRL_CDC_PASS_SEAT_SLD_FWD_ST            :"vehctrl/CdcPassSeatSldFwdSt"
//主驾座椅前端向上调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_FRNT_UPW_ST                :"vehctrl/CdcDrvrFrntUpwSt"
//主驾座椅垂直向下调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_RE_DWNWD_ST                :"vehctrl/CdcDrvrReDwnwdSt"
//主驾座椅垂直向上调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_RE_UPWD_ST                 :"vehctrl/CdcDrvrReUpwdSt"
//主驾座椅水平向前调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_SLD_BACKW_ST               :"vehctrl/CdcDrvrSldBackwSt"
//主驾座椅水平向后调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_SLD_FWD_ST                 :"vehctrl/CdcDrvrSldFwdSt"
//主驾座椅靠背向后调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_BACK_BACK_ST               :"vehctrl/CdcDrvrBackBackSt"
//主驾座椅靠背向前调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_BACK_FWD_ST                :"vehctrl/CdcDrvrBackFwdSt"
//主驾座椅前端向下调节设置
property string t_TOPIC_VEHCTRL_CDC_DRVR_FRNT_DWNWD_ST              :"vehctrl/CdcDrvrFrntDwnwdSt"
//整车状态(防盗|...)
property string t_IPC_BODY_INFO_STATUS                              :"BodyInfo/Status"
//油箱盖开闭状态
property string t_IPC_BODY_INFO_FEUL_PORT                           :"BodyInfo/FeulPort"
//油箱盖开闭状态 Set 
property string t_IPC_BODY_INFO_FEUL_PORT_SET                       :"BodyInfo/FeulPort/Set"
//统一充电口开闭
property string t_IPC_BODY_INFO_CHARGE_PORT                         :"BodyInfo/ChargePort"
//直流充电口开闭状态
property string t_IPC_BODY_INFO_DCCHARGE_PORT                       :"BodyInfo/DCChargePort"
//交流充电口开闭状态
property string t_IPC_BODY_INFO_ACCHARGE_PORT                       :"BodyInfo/ACChargePort"
//直流充电口插线状态
property string t_IPC_BODY_INFO_DCCHARGE_PLUGGED                    :"BodyInfo/DCChargePlugged"
//交流充电口插线状态
property string t_IPC_BODY_INFO_ACCHARGE_PLUGGED                    :"BodyInfo/ACChargePlugged"
//开闭状态(左前门 右前门 左后门 右后门 前舱盖(set) 后尾门(set) )
property string t_IPC_BODY_INFO_DOOR                                :"BodyInfo/Door"
//左右后门儿童锁状态  (position = RL, RR)
property string t_IPC_BODY_INFO_CHILD_SAFETY_LOCK                   :"BodyInfo/ChildSafetyLock"
//尾门开启角度
property string t_IPC_BODY_INFO_TRUNK_DOOR_OPEN_DEGREE              :"BodyInfo/TrunkDoorOpenDegree"
//门锁状态(左前门 右前门 左后门 右后门 后备箱)
property string t_IPC_BODY_INFO_DOOR_LOCK                           :"BodyInfo/DoorLock"
//门锁状态(左前门 右前门 左后门 右后门 后备箱) Set 
property string t_IPC_BODY_INFO_DOOR_LOCK_SET                       :"BodyInfo/DoorLock/Set"
//座椅安全带状态(主驾座椅 副驾座椅 后排左座椅 后排右座椅 后排中座椅 )
property string t_IPC_BODY_INFO_SEAT_BELT                           :"BodyInfo/SeatBelt"
//座椅状态(是否有人)
property string t_IPC_BODY_INFO_SEAT_OCCUPIED                       :"BodyInfo/SeatOccupied"
//座椅状态(向前向后向上向下|座椅位置)
property string t_IPC_BODY_INFO_SEAT                                :"BodyInfo/Seat"
//座椅状态(向前向后向上向下|座椅位置) Set 
property string t_IPC_BODY_INFO_SEAT_SET                            :"BodyInfo/Seat/Set"
//座椅靠背(向前向后|角度)
property string t_IPC_BODY_INFO_SEAT_BACK                           :"BodyInfo/SeatBack"
//座椅靠背(向前向后|角度) Set 
property string t_IPC_BODY_INFO_SEAT_BACK_SET                       :"BodyInfo/SeatBack/Set"
//座椅前段(向上向下|角度)
property string t_IPC_BODY_INFO_SEAT_CUSHION                        :"BodyInfo/SeatCushion"
//座椅前段(向上向下|角度) Set 
property string t_IPC_BODY_INFO_SEAT_CUSHION_SET                    :"BodyInfo/SeatCushion/Set"
//座椅记忆设置
property string t_IPC_BODY_INFO_SEAT_MEMORY                         :"BodyInfo/SeatMemory"
//座椅记忆设置 Set 
property string t_IPC_BODY_INFO_SEAT_MEMORY_SET                     :"BodyInfo/SeatMemory/Set"
//车窗 (position = FL, FR, RL, RR, OUTSIDE_TOP)
property string t_IPC_BODY_INFO_WINDOW                              :"BodyInfo/Window"
//窗户遮阳帘状态(position = TOP, TOP | 1, TOP | 2, FL)
property string t_IPC_BODY_INFO_SUN_SHADE                           :"BodyInfo/SunShade"
//雨刷状态(position = FRONT, REAR)
property string t_IPC_BODY_INFO_WIPER                               :"BodyInfo/Wiper"
//轮胎胎压 (position = FL, FR, RL, RR)
property string t_IPC_BODY_INFO_TYRE_PRESSURE                       :"BodyInfo/TyrePressure"
//轮胎胎温 (position = FL, FR, RL, RR)
property string t_IPC_BODY_INFO_TYRE_TEMPERATURE                    :"BodyInfo/TyreTemperature"
//左右后视镜状态(展开|折叠|下翻...)  (position = L, R)
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR                    :"BodyInfo/RearViewMirror"
//左右后视镜状态(展开|折叠|下翻...)  (position = L, R) Set 
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_SET                :"BodyInfo/RearViewMirror/Set"
//后视镜停车自动折叠
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_AUTO_FOLD          :"BodyInfo/RearViewMirrorAutoFold"
//后视镜停车自动折叠 Set 
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_AUTO_FOLD_SET      :"BodyInfo/RearViewMirrorAutoFold/Set"
//后视镜倒车自动下翻，也就是后视镜倒车辅助
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_AUTO_TURN_DOWN     :"BodyInfo/RearViewMirrorAutoTurnDown"
//后视镜倒车自动下翻，也就是后视镜倒车辅助 Set 
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_AUTO_TURN_DOWN_SET :"BodyInfo/RearViewMirrorAutoTurnDown/Set"
//后视镜(手动)折叠
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_FOLD               :"BodyInfo/RearViewMirrorFold"
//后视镜(手动)折叠 Set 
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_FOLD_SET           :"BodyInfo/RearViewMirrorFold/Set"
//左右后视镜调整选择(Left|Right)
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_SELECT             :"BodyInfo/RearViewMirrorSelect"
//后视镜记忆
property string t_IPC_BODY_INFO_REAR_VIEW_MIRROR_MEMORY             :"BodyInfo/RearViewMirrorMemory"
//DMS工作状态(ON|OFF)
property string t_IPC_BODY_INFO_DMS                                 :"BodyInfo/DMS"
//DMS工作状态(ON|OFF) Set 
property string t_IPC_BODY_INFO_DMS_SET                             :"BodyInfo/DMS/Set"
//雷达工作状态(ON|OFF) (FRONT|REAR|LEFT_RIGHT)
property string t_IPC_BODY_INFO_RADAR                               :"BodyInfo/Radar"
//雷达工作状态(ON|OFF) (FRONT|REAR|LEFT_RIGHT) Set 
property string t_IPC_BODY_INFO_RADAR_SET                           :"BodyInfo/Radar/Set"
//行车记录仪工作状态(ON|OFF)
property string t_IPC_BODY_INFO_DVR                                 :"BodyInfo/DVR"
//车窗控制锁状态  (position = FL, FR, RL, RR)
property string t_IPC_BODY_INFO_WINDOW_LOCK                         :"BodyInfo/WindowLock"
//刹车踏板
property string t_IPC_BODY_INFO_BRAKE_PEDAL                         :"BodyInfo/BrakePedal"
//玻璃水液位
property string t_IPC_BODY_INFO_WASH_FLUID_LEVEL                    :"BodyInfo/WashFluidLevel"
//机油液位
property string t_IPC_BODY_INFO_ENGINE_OIL_LEVEL                    :"BodyInfo/EngineOilLevel"
//冷却液液位
property string t_IPC_BODY_INFO_ENGINE_COOLANT_LEVEL                :"BodyInfo/EngineCoolantLevel"
//发动机水温
property string t_IPC_BODY_INFO_ENGINE_COOLANT_TEMPERATURE          :"BodyInfo/EngineCoolantTemperature"
//氛围灯模式
property string t_IPC_BODY_INFO_MOOD_LIGHTING_MODE                  :"BodyInfo/MoodLightingMode"
//氛围灯模式 Set 
property string t_IPC_BODY_INFO_MOOD_LIGHTING_MODE_SET              :"BodyInfo/MoodLightingMode/Set"
//氛围灯状态
property string t_IPC_BODY_INFO_MOOD_LIGHTING                       :"BodyInfo/MoodLighting"
//氛围灯状态 Set 
property string t_IPC_BODY_INFO_MOOD_LIGHTING_SET                   :"BodyInfo/MoodLighting/Set"
//氛围灯颜色
property string t_IPC_BODY_INFO_MOOD_LIGHT_COLOR                    :"BodyInfo/MoodLightColor"
//氛围灯颜色 Set 
property string t_IPC_BODY_INFO_MOOD_LIGHT_COLOR_SET                :"BodyInfo/MoodLightColor/Set"
//停车自动解锁
property string t_IPC_BODY_INFO_PARKING_AUTO_UNLOCK                 :"BodyInfo/ParkingAutoUnlock"
//停车自动解锁 Set 
property string t_IPC_BODY_INFO_PARKING_AUTO_UNLOCK_SET             :"BodyInfo/ParkingAutoUnlock/Set"
//感应解闭锁
property string t_IPC_BODY_INFO_INDUCTION_UNLOCK                    :"BodyInfo/InductionUnlock"
//感应解闭锁 Set 
property string t_IPC_BODY_INFO_INDUCTION_UNLOCK_SET                :"BodyInfo/InductionUnlock/Set"
//行车自动落锁
property string t_IPC_BODY_INFO_DRIVING_AUTO_LOCK_SPEED             :"BodyInfo/DrivingAutoLockSpeed"
//行车自动落锁 Set 
property string t_IPC_BODY_INFO_DRIVING_AUTO_LOCK_SPEED_SET         :"BodyInfo/DrivingAutoLockSpeed/Set"
//离车自动闭锁关窗
property string t_IPC_BODY_INFO_LEAVING_AUTO_LOCK                   :"BodyInfo/LeavingAutoLock"
//离车自动闭锁关窗 Set 
property string t_IPC_BODY_INFO_LEAVING_AUTO_LOCK_SET               :"BodyInfo/LeavingAutoLock/Set"
//钥匙解锁模式
property string t_IPC_BODY_INFO_UNLOCK_MODE                         :"BodyInfo/UnlockMode"
//钥匙解锁模式 Set 
property string t_IPC_BODY_INFO_UNLOCK_MODE_SET                     :"BodyInfo/UnlockMode/Set"
//拖车模式
property string t_IPC_BODY_INFO_TRAILER_MODE                        :"BodyInfo/TrailerMode"
//拖车模式 Set 
property string t_IPC_BODY_INFO_TRAILER_MODE_SET                    :"BodyInfo/TrailerMode/Set"
//无线充电开关
property string t_IPC_BODY_INFO_WIRELESS_CHARGE_SWITCH              :"BodyInfo/WirelessChargeSwitch"
//无线充电开关 Set 
property string t_IPC_BODY_INFO_WIRELESS_CHARGE_SWITCH_SET          :"BodyInfo/WirelessChargeSwitch/Set"
//无线充电状态
property string t_IPC_BODY_INFO_WIRELESS_CHARGE_STATUS              :"BodyInfo/WirelessChargeStatus"
//制动助力模式
property string t_IPC_BODY_INFO_BRAKE_BOOSTER_MODE                  :"BodyInfo/BrakeBoosterMode"
//制动助力模式 Set 
property string t_IPC_BODY_INFO_BRAKE_BOOSTER_MODE_SET              :"BodyInfo/BrakeBoosterMode/Set"
//蠕行功能
property string t_IPC_BODY_INFO_CRAWL_CONTROL                       :"BodyInfo/CrawlControl"
//蠕行功能 Set 
property string t_IPC_BODY_INFO_CRAWL_CONTROL_SET                   :"BodyInfo/CrawlControl/Set"
//加速模式(fast|normal|...)
property string t_IPC_BODY_INFO_ACCELERATION_MODE                   :"BodyInfo/AccelerationMode"
//加速模式(fast|normal|...) Set 
property string t_IPC_BODY_INFO_ACCELERATION_MODE_SET               :"BodyInfo/AccelerationMode/Set"
//背光亮度
property string t_IPC_BODY_INFO_DIMMER_LEVEL                        :"BodyInfo/DimmerLevel"
//背光亮度 Set 
property string t_IPC_BODY_INFO_DIMMER_LEVEL_SET                    :"BodyInfo/DimmerLevel/Set"
//交流充电电流限值
property string t_IPC_BODY_INFO_ACCHARGE_CURRENT_LIMIT              :"BodyInfo/ACChargeCurrentLimit"
//交流充电电流限值 Set 
property string t_IPC_BODY_INFO_ACCHARGE_CURRENT_LIMIT_SET          :"BodyInfo/ACChargeCurrentLimit/Set"
//充电插口自动解锁
property string t_IPC_BODY_INFO_CHARGE_AUTO_UNLOCK                  :"BodyInfo/ChargeAutoUnlock"
//充电插口自动解锁 Set 
property string t_IPC_BODY_INFO_CHARGE_AUTO_UNLOCK_SET              :"BodyInfo/ChargeAutoUnlock/Set"
//长按钥匙自动通风
property string t_IPC_BODY_INFO_KEY_LONG_PRESS_AUTO_WIND            :"BodyInfo/KeyLongPressAutoWind"
//长按钥匙自动通风 Set 
property string t_IPC_BODY_INFO_KEY_LONG_PRESS_AUTO_WIND_SET        :"BodyInfo/KeyLongPressAutoWind/Set"
//钥匙开锁自动通风
property string t_IPC_BODY_INFO_KEY_UNLOCK_AUTO_WIND                :"BodyInfo/KeyUnlockAutoWind"
//钥匙开锁自动通风 Set 
property string t_IPC_BODY_INFO_KEY_UNLOCK_AUTO_WIND_SET            :"BodyInfo/KeyUnlockAutoWind/Set"
//雨刮器档位
property string t_IPC_BODY_INFO_WIPER_LEVEL                         :"BodyInfo/WiperLevel"
//蓝牙钥匙是否允许访问
property string t_IPC_BODY_INFO_BTKEY_PERMISSION                    :"BodyInfo/BTKeyPermission"
//蓝牙钥匙是否允许访问 Set 
property string t_IPC_BODY_INFO_BTKEY_PERMISSION_SET                :"BodyInfo/BTKeyPermission/Set"
//座椅礼让(分前后排)
property string t_IPC_BODY_INFO_EASY_ENTRY                          :"BodyInfo/EasyEntry"
//座椅礼让(分前后排) Set 
property string t_IPC_BODY_INFO_EASY_ENTRY_SET                      :"BodyInfo/EasyEntry/Set"
//拨打道路救援电话
property string t_IPC_BODY_INFO_CALL_ROADSIDE_ASSISTANCE            :"BodyInfo/CallRoadsideAssistance"
//拨打道路救援电话 Set 
property string t_IPC_BODY_INFO_CALL_ROADSIDE_ASSISTANCE_SET        :"BodyInfo/CallRoadsideAssistance/Set"
//挂断道路救援电话
property string t_IPC_BODY_INFO_HANGUP_ROADSIDE_ASSISTANCE          :"BodyInfo/HangupRoadsideAssistance"
//挂断道路救援电话 Set 
property string t_IPC_BODY_INFO_HANGUP_ROADSIDE_ASSISTANCE_SET      :"BodyInfo/HangupRoadsideAssistance/Set"
//雨刮器维修模式
property string t_IPC_BODY_INFO_WIPER_SERVICE_MODE                  :"BodyInfo/WiperServiceMode"
//雨刮器维修模式 Set 
property string t_IPC_BODY_INFO_WIPER_SERVICE_MODE_SET              :"BodyInfo/WiperServiceMode/Set"
//拨打紧急救援电话
property string t_IPC_BODY_INFO_CALL_EMERGENCY_ASSISTANCE           :"BodyInfo/CallEmergencyAssistance"
//拨打紧急救援电话 Set 
property string t_IPC_BODY_INFO_CALL_EMERGENCY_ASSISTANCE_SET       :"BodyInfo/CallEmergencyAssistance/Set"
//挂断紧急救援电话
property string t_IPC_BODY_INFO_HANGUP_EMERGENCY_ASSISTANCE         :"BodyInfo/HangupEmergencyAssistance"
//挂断紧急救援电话 Set 
property string t_IPC_BODY_INFO_HANGUP_EMERGENCY_ASSISTANCE_SET     :"BodyInfo/HangupEmergencyAssistance/Set"
//行驶主动加热(电池)
property string t_IPC_BODY_INFO_BATTERY_AUTO_HEATING                :"BodyInfo/BatteryAutoHeating"
//行驶主动加热(电池) Set 
property string t_IPC_BODY_INFO_BATTERY_AUTO_HEATING_SET            :"BodyInfo/BatteryAutoHeating/Set"
//即时加热(电池)
property string t_IPC_BODY_INFO_BATTERY_HEATING                     :"BodyInfo/BatteryHeating"
//即时加热(电池) Set 
property string t_IPC_BODY_INFO_BATTERY_HEATING_SET                 :"BodyInfo/BatteryHeating/Set"
//充电桩(蓝牙)(主动)连接设置(ON|OFF)
property string t_IPC_BODY_INFO_CHARGE_PILE_BTCONNECT               :"BodyInfo/ChargePileBTConnect"
//充电桩(蓝牙)(主动)连接设置(ON|OFF) Set 
property string t_IPC_BODY_INFO_CHARGE_PILE_BTCONNECT_SET           :"BodyInfo/ChargePileBTConnect/Set"
//蓝牙连接请求
property string t_IPC_BODY_INFO_BTCONNECT_REQUEST                   :"BodyInfo/BTConnectRequest"
//蓝牙断开连接请求
property string t_IPC_BODY_INFO_BTDISCONNECT_REQUEST                :"BodyInfo/BTDisconnectRequest"
//蓝牙删除配对请求
property string t_IPC_BODY_INFO_BTDELETE_PAIR_REQUEST               :"BodyInfo/BTDeletePairRequest"
//HUD开关
property string t_IPC_BODY_INFO_HUD                                 :"BodyInfo/HUD"
//HUD开关 Set 
property string t_IPC_BODY_INFO_HUD_SET                             :"BodyInfo/HUD/Set"
//HUD亮度等级
property string t_IPC_BODY_INFO_HUDBRIGHTNESS                       :"BodyInfo/HUDBrightness"
//HUD亮度等级 Set 
property string t_IPC_BODY_INFO_HUDBRIGHTNESS_SET                   :"BodyInfo/HUDBrightness/Set"
//HUD亮度自动调节
property string t_IPC_BODY_INFO_HUDBRIGHTNESS_AUTO_ADJUSTMENT       :"BodyInfo/HUDBrightnessAutoAdjustment"
//HUD亮度自动调节 Set 
property string t_IPC_BODY_INFO_HUDBRIGHTNESS_AUTO_ADJUSTMENT_SET   :"BodyInfo/HUDBrightnessAutoAdjustment/Set"
//HUD高度
property string t_IPC_BODY_INFO_HUDHEIGHT                           :"BodyInfo/HUDHeight"
//HUD高度 Set 
property string t_IPC_BODY_INFO_HUDHEIGHT_SET                       :"BodyInfo/HUDHeight/Set"
//HUD主题
property string t_IPC_BODY_INFO_HUDTHEME                            :"BodyInfo/HUDTheme"
//HUD主题 Set 
property string t_IPC_BODY_INFO_HUDTHEME_SET                        :"BodyInfo/HUDTheme/Set"
//HUD显示模式
property string t_IPC_BODY_INFO_HUDDISPLAY_MODE                     :"BodyInfo/HUDDisplayMode"
//HUD显示模式 Set 
property string t_IPC_BODY_INFO_HUDDISPLAY_MODE_SET                 :"BodyInfo/HUDDisplayMode/Set"
//HUD视频播放模式(车机|HUD)
property string t_IPC_BODY_INFO_HUDVIDEO                            :"BodyInfo/HUDVideo"
//HUD视频播放模式(车机|HUD) Set 
property string t_IPC_BODY_INFO_HUDVIDEO_SET                        :"BodyInfo/HUDVideo/Set"
//低速行人报警开关(ON|OFF)
property string t_IPC_BODY_INFO_LOW_SPEED_PEDESTRIAN_ALARM          :"BodyInfo/LowSpeedPedestrianAlarm"
//低速行人报警开关(ON|OFF) Set 
property string t_IPC_BODY_INFO_LOW_SPEED_PEDESTRIAN_ALARM_SET      :"BodyInfo/LowSpeedPedestrianAlarm/Set"
//低速行人报警声音类型
//低速行人报警声音类型 Set 
//音量随速调整(ON|OFF)
property string t_IPC_BODY_INFO_VOLUME_WITH_SPEED                   :"BodyInfo/VolumeWithSpeed"
//音量随速调整(ON|OFF) Set 
property string t_IPC_BODY_INFO_VOLUME_WITH_SPEED_SET               :"BodyInfo/VolumeWithSpeed/Set"
//唤醒词(选择)
property string t_IPC_BODY_INFO_SAY_HI_SOUND                        :"BodyInfo/SayHiSound"
//唤醒词(选择) Set 
property string t_IPC_BODY_INFO_SAY_HI_SOUND_SET                    :"BodyInfo/SayHiSound/Set"
//个性化提示音(选择)
property string t_IPC_BODY_INFO_CUE_TONE                            :"BodyInfo/CueTone"
//个性化提示音(选择) Set 
property string t_IPC_BODY_INFO_CUE_TONE_SET                        :"BodyInfo/CueTone/Set"
//车外气温(payload里要有数值+摄氏华氏单位)
property string t_IPC_SENSOR_OUTSIDE_TEMPERATURE                    :"Sensor/OutsideTemperature"
//车内气温(区别于空调设定温度)
property string t_IPC_SENSOR_INSIDE_TEMPERATURE                     :"Sensor/InsideTemperature"
//车外空气质量
property string t_IPC_SENSOR_OUTSIDE_AIR_QUALITY                    :"Sensor/OutsideAirQuality"
//车内空气质量
property string t_IPC_SENSOR_INSIDE_AIR_QUALITY                     :"Sensor/InsideAirQuality"
//环境光照强度
property string t_IPC_SENSOR_LIGHT_INTENSITY                        :"Sensor/LightIntensity"
//瞬时电耗
property string t_IPC_ENERGY_INFO_POWER_CONSUMPTION                 :"EnergyInfo/PowerConsumption"
//能量流向
property string t_IPC_ENERGY_INFO_POWER_FLOW_DIRECTION              :"EnergyInfo/PowerFlowDirection"
//动力电池电压
property string t_IPC_ENERGY_INFO_HIGH_VOLT_BATTERY_VOLTAGE         :"EnergyInfo/HighVoltBatteryVoltage"
//动力电池电流
property string t_IPC_ENERGY_INFO_HIGH_VOLT_BATTERY_CURRENT         :"EnergyInfo/HighVoltBatteryCurrent"
//低压蓄电池电压
property string t_IPC_ENERGY_INFO_LOW_VOLT_BATTERY_VOLTAGE          :"EnergyInfo/LowVoltBatteryVoltage"
//低压蓄电池电流
property string t_IPC_ENERGY_INFO_LOW_VOLT_BATTERY_CURRENT          :"EnergyInfo/LowVoltBatteryCurrent"
//动力电池百分比
property string t_IPC_ENERGY_INFO_SO_CPERCENT                       :"EnergyInfo/SoCPercent"
//动力电池续航剩余里程
property string t_IPC_ENERGY_INFO_SO_CRESIDUAL_RANGE                :"EnergyInfo/SoCResidualRange"
//油量百分比
property string t_IPC_ENERGY_INFO_FUEL_PERCENT                      :"EnergyInfo/FuelPercent"
//油续航剩余里程
property string t_IPC_ENERGY_INFO_FUEL_RESIDUAL_RANGE               :"EnergyInfo/FuelResidualRange"
//剩余氢气量百分比
property string t_IPC_ENERGY_INFO_HYDROGEN_PERCENT                  :"EnergyInfo/HydrogenPercent"
//氢剩余里程
property string t_IPC_ENERGY_INFO_HYDROGEN_REMAIN_RANGE             :"EnergyInfo/HydrogenRemainRange"
//预约充电开始时间
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_START_TIME       :"EnergyInfo/ScheduledChargeStartTime"
//预约充电开始时间 Set 
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_START_TIME_SET   :"EnergyInfo/ScheduledChargeStartTime/Set"
//预约充电结束时间
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_STOP_TIME        :"EnergyInfo/ScheduledChargeStopTime"
//预约充电结束时间 Set 
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_STOP_TIME_SET    :"EnergyInfo/ScheduledChargeStopTime/Set"
//预约充电模式(即插即充/预约充电)
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_MODE             :"EnergyInfo/ScheduledChargeMode"
//预约充电模式(即插即充/预约充电) Set 
property string t_IPC_ENERGY_INFO_SCHEDULED_CHARGE_MODE_SET         :"EnergyInfo/ScheduledChargeMode/Set"
//充电目标值
property string t_IPC_ENERGY_INFO_CHARGE_SO_CTHRESHOLD              :"EnergyInfo/ChargeSoCThreshold"
//充电目标值 Set 
property string t_IPC_ENERGY_INFO_CHARGE_SO_CTHRESHOLD_SET          :"EnergyInfo/ChargeSoCThreshold/Set"
//放电阈值
property string t_IPC_ENERGY_INFO_DISCHARGE_SO_CTHRESHOLD           :"EnergyInfo/DischargeSoCThreshold"
//放电阈值 Set 
property string t_IPC_ENERGY_INFO_DISCHARGE_SO_CTHRESHOLD_SET       :"EnergyInfo/DischargeSoCThreshold/Set"
//充电类型(直流/交流)
property string t_IPC_ENERGY_INFO_CHARGE_TYPE                       :"EnergyInfo/ChargeType"
//充电电压
property string t_IPC_ENERGY_INFO_CHARGE_VOLTAGE                    :"EnergyInfo/ChargeVoltage"
//充电电流
property string t_IPC_ENERGY_INFO_CHARGE_CURRENT                    :"EnergyInfo/ChargeCurrent"
//充电剩余时间（分钟）
property string t_IPC_ENERGY_INFO_CHARGE_REMAIN_TIME                :"EnergyInfo/ChargeRemainTime"
//本次累计充电电量
property string t_IPC_ENERGY_INFO_CHARGEK_WH                        :"EnergyInfo/ChargekWh"
//充电增加里程(payload里要有单位：公里|英里)
property string t_IPC_ENERGY_INFO_CHARGE_INCREASED_RANGE            :"EnergyInfo/ChargeIncreasedRange"
//放电电压
property string t_IPC_ENERGY_INFO_DISCHARGE_VOLTAGE                 :"EnergyInfo/DischargeVoltage"
//放电电流
property string t_IPC_ENERGY_INFO_DISCHARGE_CURRENT                 :"EnergyInfo/DischargeCurrent"
//钥匙电量
property string t_IPC_ENERGY_INFO_KEY_BATTERY_LEVEL                 :"EnergyInfo/KeyBatteryLevel"
//能量回收模式
property string t_IPC_ENERGY_INFO_ENERGY_RECOVERY_MODE              :"EnergyInfo/EnergyRecoveryMode"
//能量回收模式 Set 
property string t_IPC_ENERGY_INFO_ENERGY_RECOVERY_MODE_SET          :"EnergyInfo/EnergyRecoveryMode/Set"
//瞬时剩余里程(payload里要有单位：公里|英里)
property string t_IPC_ENERGY_INFO_RESIDUAL_RANGE                    :"EnergyInfo/ResidualRange"
//10km平均剩余里程(payload里要有单位：公里|英里)
property string t_IPC_ENERGY_INFO_RESIDUAL_RANGE_BY10KM             :"EnergyInfo/ResidualRangeBy10km"
//25km平均剩余里程(payload里要有单位：公里|英里)
property string t_IPC_ENERGY_INFO_RESIDUAL_RANGE_BY25KM             :"EnergyInfo/ResidualRangeBy25km"
//50km平均剩余里程(payload里要有单位：公里|英里)
property string t_IPC_ENERGY_INFO_RESIDUAL_RANGE_BY50KM             :"EnergyInfo/ResidualRangeBy50km"
//工况平均能耗值
property string t_IPC_ENERGY_INFO_AVERAGE_ENERGY_CONSUMPTION        :"EnergyInfo/AverageEnergyConsumption"
//剩余能量百分比|距离显示选项
property string t_IPC_ENERGY_INFO_RESIDUAL_ENERGY_DISPLAY_MODE      :"EnergyInfo/ResidualEnergyDisplayMode"
//能耗选项：计算剩余里程所用工况(CLTC|WLTC|NEDC)
property string t_IPC_ENERGY_INFO_ENERGY_CONSUMPTION_ASSESSMENT     :"EnergyInfo/EnergyConsumptionAssessment"
//电量保持目标
property string t_IPC_ENERGY_INFO_SO_CHOLDING                       :"EnergyInfo/SoCHolding"
//电量保持目标 Set 
property string t_IPC_ENERGY_INFO_SO_CHOLDING_SET                   :"EnergyInfo/SoCHolding/Set"
//能量管理模式(纯电优先|混动|电量保持)
property string t_IPC_ENERGY_INFO_ENERGY_MANAGEMENT_MODE            :"EnergyInfo/EnergyManagementMode"
//能量管理模式(纯电优先|混动|电量保持) Set 
property string t_IPC_ENERGY_INFO_ENERGY_MANAGEMENT_MODE_SET        :"EnergyInfo/EnergyManagementMode/Set"
//能量管理模式记忆设置
property string t_IPC_ENERGY_INFO_ENERGY_MANAGEMENT_MODE_MEMORY     :"EnergyInfo/EnergyManagementModeMemory"
//能量管理模式记忆设置 Set 
property string t_IPC_ENERGY_INFO_ENERGY_MANAGEMENT_MODE_MEMORY_SET :"EnergyInfo/EnergyManagementModeMemory/Set"
//电源状态（IGN）(ON|OFF|ACC|START)
property string t_IPC_DRIVING_INFO_POWER_STATUS                     :"DrivingInfo/PowerStatus"
//整车能源工作模式(油|电|气|混|...)
property string t_IPC_DRIVING_INFO_ENERGY_MODE                      :"DrivingInfo/EnergyMode"
//车速
property string t_IPC_DRIVING_INFO_SPEED                            :"DrivingInfo/Speed"
//档位
property string t_IPC_DRIVING_INFO_GEAR                             :"DrivingInfo/Gear"
//驾驶模式
property string t_IPC_DRIVING_INFO_DRIVING_MODE                     :"DrivingInfo/DrivingMode"
//驾驶模式 Set 
property string t_IPC_DRIVING_INFO_DRIVING_MODE_SET                 :"DrivingInfo/DrivingMode/Set"
//电机转速
property string t_IPC_DRIVING_INFO_MOTOR_SPEED                      :"DrivingInfo/MotorSpeed"
//电机功率(能量回收时为负值)
property string t_IPC_DRIVING_INFO_ENGINE_POWER                     :"DrivingInfo/EnginePower"
//发动机转速
property string t_IPC_DRIVING_INFO_ENGINE_ROTATE_SPEED              :"DrivingInfo/EngineRotateSpeed"
//总行驶时间(不可清零 h)
property string t_IPC_DRIVING_INFO_TOTAL_DRIVE_TIME                 :"DrivingInfo/TotalDriveTime"
//总行驶距离(不可清零 km)
property string t_IPC_DRIVING_INFO_TOTAL_DRIVE_DISTANCE             :"DrivingInfo/TotalDriveDistance"
//累计行驶时间(h)
property string t_IPC_DRIVING_INFO_ACCUMULATIVE_DRIVE_TIME          :"DrivingInfo/AccumulativeDriveTime"
//累计行驶距离(payload里要有单位：公里|英里)
property string t_IPC_DRIVING_INFO_ACCUMULATIVE_DRIVE_RANGE         :"DrivingInfo/AccumulativeDriveRange"
//累计行驶平均车速(payload里要有单位：公里/h|英里/h)
property string t_IPC_DRIVING_INFO_ACCUMULATIVE_AVERAGE_SPEED       :"DrivingInfo/AccumulativeAverageSpeed"
//当前行程行驶时间(h)
property string t_IPC_DRIVING_INFO_TRIP_DRIVE_TIME                  :"DrivingInfo/TripDriveTime"
//当前行程行驶距离(payload里要有单位：公里|英里)
property string t_IPC_DRIVING_INFO_TRIP_DRIVE_RANGE                 :"DrivingInfo/TripDriveRange"
//当前行程行驶平均车速(payload里要有单位：公里/h|英里/h)
property string t_IPC_DRIVING_INFO_TRIP_AVERAGE_SPEED               :"DrivingInfo/TripAverageSpeed"
//方向盘转向角度
property string t_IPC_DRIVING_INFO_STEERING_WHEEL_ANGLE             :"DrivingInfo/SteeringWheelAngle"
//方向盘角速度
property string t_IPC_DRIVING_INFO_STEERING_WHEEL_SPEED             :"DrivingInfo/SteeringWheelSpeed"
//油门深度
property string t_IPC_DRIVING_INFO_ACCELERATE_DEEPNESS              :"DrivingInfo/AccelerateDeepness"
//制动深度
property string t_IPC_DRIVING_INFO_BRAKE_DEEPNESS                   :"DrivingInfo/BrakeDeepness"
//保养时间
property string t_IPC_DRIVING_INFO_MAINTENANCE_TIME                 :"DrivingInfo/MaintenanceTime"
//保养里程
property string t_IPC_DRIVING_INFO_MAINTENANCE_MILEAGE              :"DrivingInfo/MaintenanceMileage"
//行驶信息设置(总计|小计|驾驶循环内|补能后...)
property string t_IPC_DRIVING_INFO_DRIVING_INFO_TYPE                :"DrivingInfo/DrivingInfoType"
//油模式总计行驶里程
property string t_IPC_DRIVING_INFO_FUEL_TOTAL_DRIVE_RANGE           :"DrivingInfo/FuelTotalDriveRange"
//油模式累计(小计)行驶里程
property string t_IPC_DRIVING_INFO_FUEL_ACCUMULATIVE_DRIVE_RANGE    :"DrivingInfo/FuelAccumulativeDriveRange"
//油模式当前行驶里程
property string t_IPC_DRIVING_INFO_FUEL_TRIP_DRIVE_RANGE            :"DrivingInfo/FuelTripDriveRange"
//油模式加油后行驶里程
property string t_IPC_DRIVING_INFO_FUEL_LAST_REFUEL_DRIVE_RANGE     :"DrivingInfo/FuelLastRefuelDriveRange"
//油模式总计行驶时长
property string t_IPC_DRIVING_INFO_FUEL_TOTAL_DRIVE_TIME            :"DrivingInfo/FuelTotalDriveTime"
//油模式累计(小计)行驶时长
property string t_IPC_DRIVING_INFO_FUEL_ACCUMULATIVE_DRIVE_TIME     :"DrivingInfo/FuelAccumulativeDriveTime"
//油模式当前行驶时长
property string t_IPC_DRIVING_INFO_FUEL_TRIP_DRIVE_TIME             :"DrivingInfo/FuelTripDriveTime"
//油模式加油后行驶时长
property string t_IPC_DRIVING_INFO_FUEL_LAST_REFUEL_DRIVE_TIME      :"DrivingInfo/FuelLastRefuelDriveTime"
//油模式总计平均油耗
property string t_IPC_DRIVING_INFO_FUEL_TOTAL_AVERAGE_CONSUMPTION   :"DrivingInfo/FuelTotalAverageConsumption"
//油模式累计(小计)平均油耗
property string t_IPC_DRIVING_INFO_FUEL_ACCUMULATIVE_AVERAGE_CONSUMPTION:"DrivingInfo/FuelAccumulativeAverageConsumption"
//油模式加油后平均油耗
property string t_IPC_DRIVING_INFO_FUEL_LAST_REFUEL_AVERAGE_CONSUMPTION:"DrivingInfo/FuelLastRefuelAverageConsumption"
//油模式驾驶循环内平均油耗
property string t_IPC_DRIVING_INFO_FUEL_DRIVE_CYCLE_AVERAGE_CONSUMPTION:"DrivingInfo/FuelDriveCycleAverageConsumption"
//电模式总计行驶里程
property string t_IPC_DRIVING_INFO_EVTOTAL_DRIVE_RANGE              :"DrivingInfo/EVTotalDriveRange"
//电模式累计(小计)行驶里程
property string t_IPC_DRIVING_INFO_EVACCUMULATIVE_DRIVE_RANGE       :"DrivingInfo/EVAccumulativeDriveRange"
//电模式当前行驶里程
property string t_IPC_DRIVING_INFO_EVTRIP_DRIVE_RANGE               :"DrivingInfo/EVTripDriveRange"
//电模式充电后行驶里程
property string t_IPC_DRIVING_INFO_EVLAST_CHARGE_DRIVE_RANGE        :"DrivingInfo/EVLastChargeDriveRange"
//电模式当前行驶时长
property string t_IPC_DRIVING_INFO_EVTRIP_DRIVE_TIME                :"DrivingInfo/EVTripDriveTime"
//电模式总计行驶时长
property string t_IPC_DRIVING_INFO_EVTOTAL_DRIVE_TIME               :"DrivingInfo/EVTotalDriveTime"
//电模式累计(小计)行驶时长
property string t_IPC_DRIVING_INFO_EVACCUMULATIVE_DRIVE_TIME        :"DrivingInfo/EVAccumulativeDriveTime"
//电模式充电后行驶时长
property string t_IPC_DRIVING_INFO_EVLAST_CHARGE_DRIVE_TIME         :"DrivingInfo/EVLastChargeDriveTime"
//电模式总计平均电耗
property string t_IPC_DRIVING_INFO_EVTOTAL_AVERAGE_CONSUMPTION      :"DrivingInfo/EVTotalAverageConsumption"
//电模式累计(小计)平均电耗
property string t_IPC_DRIVING_INFO_EVACCUMULATIVE_AVERAGE_CONSUMPTION:"DrivingInfo/EVAccumulativeAverageConsumption"
//电模式充电后平均电耗
property string t_IPC_DRIVING_INFO_EVLAST_CHARGE_AVERAGE_CONSUMPTION:"DrivingInfo/EVLastChargeAverageConsumption"
//电模式驾驶循环内平均电耗
property string t_IPC_DRIVING_INFO_EVDRIVE_CYCLE_AVERAGE_CONSUMPTION:"DrivingInfo/EVDriveCycleAverageConsumption"
//重置长期驾驶信息
property string t_IPC_DRIVING_INFO_RESET_TOTAL_DRIVING_INFO         :"DrivingInfo/ResetTotalDrivingInfo"
//重置累计(小计)驾驶里程
property string t_IPC_DRIVING_INFO_RESET_ACCUMULATIVE_DRIVE_RANGE   :"DrivingInfo/ResetAccumulativeDriveRange"
//Ready
property string t_IPC_TELLTALE_READY                                :"Telltale/Ready"
//电子手刹
property string t_IPC_TELLTALE_EPB                                  :"Telltale/EPB"
//电子手刹 Set 
property string t_IPC_TELLTALE_EPB_SET                              :"Telltale/EPB/Set"
//充电枪连接指示灯状态
property string t_IPC_TELLTALE_CHARGE_CONNECTION                    :"Telltale/ChargeConnection"
//充电状态指示灯状态
property string t_IPC_TELLTALE_CHARGE_STATE                         :"Telltale/ChargeState"
//电子助力转向系统工作指示灯状态
property string t_IPC_TELLTALE_EPS                                  :"Telltale/EPS"
//电子助力转向系统工作指示灯状态 Set 
property string t_IPC_TELLTALE_EPS_SET                              :"Telltale/EPS/Set"
//车身电子稳定系统工作指示灯状态
property string t_IPC_TELLTALE_ESC                                  :"Telltale/ESC"
//车身电子稳定系统工作指示灯状态 Set 
property string t_IPC_TELLTALE_ESC_SET                              :"Telltale/ESC/Set"
//胎压检测系统工作指示灯状态
property string t_IPC_TELLTALE_TPMS                                 :"Telltale/TPMS"
//电池低温加热工作指示灯状态
property string t_IPC_TELLTALE_POWER_BATTERY_HEATING                :"Telltale/PowerBatteryHeating"
//220V放电状态工作指示灯状态
property string t_IPC_TELLTALE_DISCHARGE_STATE                      :"Telltale/DischargeState"
//自动驻车系统工作指示灯状态
property string t_IPC_TELLTALE_AUTO_HOLD                            :"Telltale/AutoHold"
//自动驻车系统工作指示灯状态 Set 
property string t_IPC_TELLTALE_AUTO_HOLD_SET                        :"Telltale/AutoHold/Set"
//燃料电池工作指示灯状态
property string t_IPC_TELLTALE_FEUL_CELL_STATE                      :"Telltale/FeulCellState"
//冷却液加注工作指示灯状态
property string t_IPC_TELLTALE_COOLANT                              :"Telltale/Coolant"
//雾灯状态(position = FRONT, REAR)
property string t_IPC_LIGHT_FOG_LAMP                                :"Light/FogLamp"
//雾灯状态(position = FRONT, REAR) Set 
property string t_IPC_LIGHT_FOG_LAMP_SET                            :"Light/FogLamp/Set"
//位置灯(示廓灯)状态
property string t_IPC_LIGHT_POSITION_LAMP                           :"Light/PositionLamp"
//位置灯(示廓灯)状态 Set 
property string t_IPC_LIGHT_POSITION_LAMP_SET                       :"Light/PositionLamp/Set"
//近光灯状态
property string t_IPC_LIGHT_LOW_BEAM                                :"Light/LowBeam"
//近光灯状态 Set 
property string t_IPC_LIGHT_LOW_BEAM_SET                            :"Light/LowBeam/Set"
//远光灯状态
property string t_IPC_LIGHT_HIGH_BEAM                               :"Light/HighBeam"
//左转向灯状态
property string t_IPC_LIGHT_TURN_LEFT                               :"Light/TurnLeft"
//右转向灯状态
property string t_IPC_LIGHT_TURN_RIGHT                              :"Light/TurnRight"
//危险报警灯(双闪)状态
property string t_IPC_LIGHT_HAZARD_WARNING                          :"Light/HazardWarning"
//危险报警灯(双闪)状态 Set 
property string t_IPC_LIGHT_HAZARD_WARNING_SET                      :"Light/HazardWarning/Set"
//自动远光灯状态
property string t_IPC_LIGHT_AUTO_HIGH_BEAM                          :"Light/AutoHighBeam"
//自动远光灯状态 Set 
property string t_IPC_LIGHT_AUTO_HIGH_BEAM_SET                      :"Light/AutoHighBeam/Set"
//自动大灯状态
property string t_IPC_LIGHT_AUTO_HEAD_LAMP                          :"Light/AutoHeadLamp"
//自动大灯状态 Set 
property string t_IPC_LIGHT_AUTO_HEAD_LAMP_SET                      :"Light/AutoHeadLamp/Set"
//大灯高度
property string t_IPC_LIGHT_LIGHT_HEIGHT                            :"Light/LightHeight"
//大灯高度 Set 
property string t_IPC_LIGHT_LIGHT_HEIGHT_SET                        :"Light/LightHeight/Set"
//顶灯(阅读灯)状态(ON|OFF|AUTO/DOOR)
property string t_IPC_LIGHT_DOOR_LIGHT                              :"Light/DoorLight"
//顶灯(阅读灯)状态(ON|OFF|AUTO/DOOR) Set 
property string t_IPC_LIGHT_DOOR_LIGHT_SET                          :"Light/DoorLight/Set"
//日间行车灯状态
property string t_IPC_LIGHT_DAYTIME_RUNNING_LAMP                    :"Light/DaytimeRunningLamp"
//日间行车灯状态 Set 
property string t_IPC_LIGHT_DAYTIME_RUNNING_LAMP_SET                :"Light/DaytimeRunningLamp/Set"
//洗涤液位低提示
property string t_IPC_WARNING_WASH_FLUID_LOW                        :"Warning/WashFluidLow"
//制动液位低提示
property string t_IPC_WARNING_BRAKE_FLUID_LOW                       :"Warning/BrakeFluidLow"
//油量低提示报警
property string t_IPC_WARNING_FUEL_TANK_LOW                         :"Warning/FuelTankLow"
//发动机水温过高报警
property string t_IPC_WARNING_WATER_TEMPERATURE_HIGH                :"Warning/WaterTemperatureHigh"
//驱动功率限制报警
property string t_IPC_WARNING_LIMIT_POWER                           :"Warning/LimitPower"
//发送机机油压力报警
property string t_IPC_WARNING_ENGINE_OIL                            :"Warning/EngineOil"
//疲劳驾驶报警
property string t_IPC_WARNING_DRIVER_FATIGUE                        :"Warning/DriverFatigue"
//氢气剩余量低报警
property string t_IPC_WARNING_HYDROGEN_SURPLUS_LOW                  :"Warning/HydrogenSurplusLow"
//氢气泄露报警
property string t_IPC_WARNING_HYDROGEN_LEAKAGE                      :"Warning/HydrogenLeakage"
//动力电池低电量报警
property string t_IPC_WARNING_POWER_BATTERY_LOW                     :"Warning/PowerBatteryLow"
//电堆温度高报警
property string t_IPC_WARNING_HIGH_STACK_TEMPERATURE                :"Warning/HighStackTemperature"
//座椅安全带报警(主驾座椅 副驾座椅 后排左座椅 后排右座椅 后排中座椅 )
property string t_IPC_WARNING_SEATBELT                              :"Warning/Seatbelt"
//安全气囊故障
property string t_IPC_FAULT_AIR_BAG                                 :"Fault/AirBag"
//电机故障
property string t_IPC_FAULT_MOTOR                                   :"Fault/Motor"
//防抱死制动系统故障
property string t_IPC_FAULT_ABS                                     :"Fault/ABS"
//发动机故障
property string t_IPC_FAULT_ENGINE                                  :"Fault/Engine"
//低压电瓶故障
property string t_IPC_FAULT_LOW_VOLT_BATTERY                        :"Fault/LowVoltBattery"
//手刹制动器故障
property string t_IPC_FAULT_PARKING_BRAKE                           :"Fault/ParkingBrake"
//制动系统故障
property string t_IPC_FAULT_BRAKE_SYSTEM                            :"Fault/BrakeSystem"
//燃料电池系统故障
property string t_IPC_FAULT_FUEL_CELL_SYSTEM                        :"Fault/FuelCellSystem"
//动力系统故障
property string t_IPC_FAULT_POWER_SYSTEM                            :"Fault/PowerSystem"
//动力电池故障
property string t_IPC_FAULT_POWER_BATTERY                           :"Fault/PowerBattery"
//车身电子稳定系统故障
property string t_IPC_FAULT_ESC                                     :"Fault/ESC"
//充电相关提示
property string t_IPC_INFO_CHARGE                                   :"Info/Charge"
//放电相关提示
property string t_IPC_INFO_DISCHARGE                                :"Info/Discharge"
//电子手刹提示
property string t_IPC_INFO_EPB                                      :"Info/EPB"
//制动踏板助力不足提示
property string t_IPC_INFO_IB                                       : "Info/IB"
//车辆锁提示
property string t_IPC_INFO_LOCK                                     :"Info/Lock"
//剩余保养提示
property string t_IPC_INFO_MAINTENANCE                              :"Info/Maintenance"
//智能钥匙电池状态提示
property string t_IPC_INFO_KEY_BATTERY                              :"Info/KeyBattery"
//ACC目标横向距离
property string t_IPC_ADAS_ACCTARGET_LATERAL_RANGE                  :"ADAS/ACCTargetLateralRange"
//ACC目标车纵向距离
property string t_IPC_ADAS_ACCTARGET_LONGITUDINAL_RANGE             :"ADAS/ACCTargetLongitudinalRange"
//ACC跟车距离等级
property string t_IPC_ADAS_ACCDISTANCE_LEVEL                        :"ADAS/ACCDistanceLevel"
//AEB目标横向距离
property string t_IPC_ADAS_AEBTARGET_LATERAL_RANGE                  :"ADAS/AEBTargetLateralRange"
//AEB目标纵向距离
property string t_IPC_ADAS_AEBTARGET_LNG_RANGE                      :"ADAS/AEBTargetLngRange"
//左车道前方目标1横向距离
property string t_IPC_ADAS_FRONT_LEFT_TARGET1LATERAL_RANGE          :"ADAS/FrontLeftTarget1LateralRange"
//左车道前方目标1纵向距离
property string t_IPC_ADAS_FRONT_LEFT_TARGET1LONGITUDINAL_RANGE     :"ADAS/FrontLeftTarget1LongitudinalRange"
//左车道前方目标2横向距离
property string t_IPC_ADAS_FRONT_LEFT_TARGET2LATERAL_RANGE          :"ADAS/FrontLeftTarget2LateralRange"
//左车道前方目标2纵向距离
property string t_IPC_ADAS_FRONT_LEFT_TARGET2LONGITUDINAL_RANGE     :"ADAS/FrontLeftTarget2LongitudinalRange"
//右车道前方目标1横向距离
property string t_IPC_ADAS_FRONT_RIGHT_TARGET1LATERAL_RANGE         :"ADAS/FrontRightTarget1LateralRange"
//右车道前方目标1纵向距离
property string t_IPC_ADAS_FRONT_RIGHT_TARGET1LONGITUDINAL_RANGE    :"ADAS/FrontRightTarget1LongitudinalRange"
//右车道前方目标2横向距离
property string t_IPC_ADAS_FRONT_RIGHT_TARGET2LATERAL_RANGE         :"ADAS/FrontRightTarget2LateralRange"
//右车道前方目标2纵向距离
property string t_IPC_ADAS_FRONT_RIGHT_TARGET2LONGITUDINAL_RANGE    :"ADAS/FrontRightTarget2LongitudinalRange"
//本车道行人目标1横向距离
property string t_IPC_ADAS_HOST_LANE_LATERAL_RANGE1                 :"ADAS/HostLaneLateralRange1"
//本车道行人目标1纵向距离
property string t_IPC_ADAS_HOST_LANE_LONGITUDINAL_RANGE1            :"ADAS/HostLaneLongitudinalRange1"
//本车道潜在目标横向距离
property string t_IPC_ADAS_HOST_LANE_POTENTIAL_TARGET_LATERAL_RANGE :"ADAS/HostLanePotentialTargetLateralRange"
//本车道潜在目标纵向距离
property string t_IPC_ADAS_HOST_LANE_POTENTIAL_TARGET_LONGITUDINAL_RANGE:"ADAS/HostLanePotentialTargetLongitudinalRange"
//车辆中心到左侧车道线的距离
property string t_IPC_ADAS_LEFT_LANE_DISTANCE                       :"ADAS/LeftLaneDistance"
//车辆中心到左左侧车道线的距离
property string t_IPC_ADAS_LEFT_LEFT_LANE_DISTANCE                  :"ADAS/LeftLeftLaneDistance"
//车辆中心到右侧车道线的距离
property string t_IPC_ADAS_RIGHT_LANE_DISTANCE                      :"ADAS/RightLaneDistance"
//车辆中心到右右侧车道线的距离
property string t_IPC_ADAS_RIGHT_RIGHT_LANE_DISTANCE                :"ADAS/RightRightLaneDistance"
//车道辅助系统
property string t_IPC_ADAS_LANE_ASSIST_SYSTEM                       :"ADAS/LaneAssistSystem"
//车道辅助系统 Set 
property string t_IPC_ADAS_LANE_ASSIST_SYSTEM_SET                   :"ADAS/LaneAssistSystem/Set"
//车道偏离辅助系统
property string t_IPC_ADAS_LANE_DEPARTUE_WARNING                    :"ADAS/LaneDepartueWarning"
//车道偏离辅助系统 Set 
property string t_IPC_ADAS_LANE_DEPARTUE_WARNING_SET                :"ADAS/LaneDepartueWarning/Set"
//集成式自适应巡航
property string t_IPC_ADAS_IACCENABLE                               :"ADAS/IACCEnable"
//集成式自适应巡航 Set 
property string t_IPC_ADAS_IACCENABLE_SET                           :"ADAS/IACCEnable/Set"
//自适应巡航
property string t_IPC_ADAS_ACCENABLE                                :"ADAS/ACCEnable"
//自适应巡航 Set 
property string t_IPC_ADAS_ACCENABLE_SET                            :"ADAS/ACCEnable/Set"
//前碰撞预警
property string t_IPC_ADAS_FORWARD_COLLISION_WARNING                :"ADAS/ForwardCollisionWarning"
//前碰撞预警 Set 
property string t_IPC_ADAS_FORWARD_COLLISION_WARNING_SET            :"ADAS/ForwardCollisionWarning/Set"
//前碰撞预警距离/灵敏度
property string t_IPC_ADAS_FCWDISTANCE                              :"ADAS/FCWDistance"
//前碰撞预警距离/灵敏度 Set 
property string t_IPC_ADAS_FCWDISTANCE_SET                          :"ADAS/FCWDistance/Set"
//空调开关状态(ON|OFF)
property string t_IPC_AC_STATUS                                     :"AC/Status"
//空调开关状态(ON|OFF) Set 
property string t_IPC_AC_STATUS_SET                                 :"AC/Status/Set"
//温度单位(摄氏度|华氏度)
property string t_IPC_AC_TEMPREATURE_UNIT                           :"AC/TempreatureUnit"
//温度单位(摄氏度|华氏度) Set 
property string t_IPC_AC_TEMPREATURE_UNIT_SET                       :"AC/TempreatureUnit/Set"
//空调当前温度(几个温区不确定，在一个payload里)
property string t_IPC_AC_TEMPERATURE                                :"AC/Temperature"
//空调当前温度(几个温区不确定，在一个payload里) Set 
property string t_IPC_AC_TEMPERATURE_SET                            :"AC/Temperature/Set"
//空调当前风量
property string t_IPC_AC_WIND_LEVEL                                 :"AC/WindLevel"
//空调当前风量 Set 
property string t_IPC_AC_WIND_LEVEL_SET                             :"AC/WindLevel/Set"
//空调出风模式
property string t_IPC_AC_WIND_MODE                                  :"AC/WindMode"
//空调出风模式 Set 
property string t_IPC_AC_WIND_MODE_SET                              :"AC/WindMode/Set"
//循环模式
property string t_IPC_AC_CYCLE_MODE                                 :"AC/CycleMode"
//循环模式 Set 
property string t_IPC_AC_CYCLE_MODE_SET                             :"AC/CycleMode/Set"
//A/C模式
property string t_IPC_AC_ACMODE                                     :"AC/ACMode"
//A/C模式 Set 
property string t_IPC_AC_ACMODE_SET                                 :"AC/ACMode/Set"
//前除霜模式
property string t_IPC_AC_FRONT_DEFROST                              :"AC/FrontDefrost"
//前除霜模式 Set 
property string t_IPC_AC_FRONT_DEFROST_SET                          :"AC/FrontDefrost/Set"
//后除霜模式
property string t_IPC_AC_REAR_DEFROST                               :"AC/RearDefrost"
//后除霜模式 Set 
property string t_IPC_AC_REAR_DEFROST_SET                           :"AC/RearDefrost/Set"
//自动除霜除雾
property string t_IPC_AC_AUTO_DEFROST_DEFOG                         :"AC/AutoDefrostDefog"
//自动除霜除雾 Set 
property string t_IPC_AC_AUTO_DEFROST_DEFOG_SET                     :"AC/AutoDefrostDefog/Set"
//自动模式
property string t_IPC_AC_AUTO_MODE                                  :"AC/AutoMode"
//自动模式 Set 
property string t_IPC_AC_AUTO_MODE_SET                              :"AC/AutoMode/Set"
//温区同步模式
property string t_IPC_AC_SYNC_MODE                                  :"AC/SyncMode"
//温区同步模式 Set 
property string t_IPC_AC_SYNC_MODE_SET                              :"AC/SyncMode/Set"
//Max AC模式
property string t_IPC_AC_MAX_AC                                     :"AC/MaxAC"
//Max AC模式 Set 
property string t_IPC_AC_MAX_AC_SET                                 :"AC/MaxAC/Set"
//加热模式
property string t_IPC_AC_HEATING_MODE                               :"AC/HeatingMode"
//加热模式 Set 
property string t_IPC_AC_HEATING_MODE_SET                           :"AC/HeatingMode/Set"
//左右后视镜加热状态(position = FL, FR)
property string t_IPC_AC_REAR_VIEW_MIRROR_HEATING                   :"AC/RearViewMirrorHeating"
//左右后视镜加热状态(position = FL, FR) Set 
property string t_IPC_AC_REAR_VIEW_MIRROR_HEATING_SET               :"AC/RearViewMirrorHeating/Set"
//座椅加热状态(position = FL, FR, RL, RR)
property string t_IPC_AC_SEAT_HEATING                               :"AC/SeatHeating"
//座椅加热状态(position = FL, FR, RL, RR) Set 
property string t_IPC_AC_SEAT_HEATING_SET                           :"AC/SeatHeating/Set"
//座椅通风状态(position = FL, FR, RL, RR)
property string t_IPC_AC_SEAT_VENTILATION                           :"AC/SeatVentilation"
//座椅通风状态(position = FL, FR, RL, RR) Set 
property string t_IPC_AC_SEAT_VENTILATION_SET                       :"AC/SeatVentilation/Set"
//方向盘加热状态
property string t_IPC_AC_STEERING_WHEEL_HEATING                     :"AC/SteeringWheelHeating"
//方向盘加热状态 Set 
property string t_IPC_AC_STEERING_WHEEL_HEATING_SET                 :"AC/SteeringWheelHeating/Set"
//定时通风
property string t_IPC_AC_VENTILATION_TIMER                          :"AC/VentilationTimer"
//定时通风 Set 
property string t_IPC_AC_VENTILATION_TIMER_SET                      :"AC/VentilationTimer/Set"
//空调自动干燥
property string t_IPC_AC_AUTO_WIND_DRYING                           :"AC/AutoWindDrying"
//空调自动干燥 Set 
property string t_IPC_AC_AUTO_WIND_DRYING_SET                       :"AC/AutoWindDrying/Set"
//离子发生器
property string t_IPC_AC_PLASMA                                     :"AC/Plasma"
//离子发生器 Set 
property string t_IPC_AC_PLASMA_SET                                 :"AC/Plasma/Set"
//电动出风口调节
property string t_IPC_AC_ELECTRIC_AIR_OUTLET                        :"AC/ElectricAirOutlet"
//电动出风口调节 Set 
property string t_IPC_AC_ELECTRIC_AIR_OUTLET_SET                    :"AC/ElectricAirOutlet/Set"
//方向盘按键事件
property string t_IPC_KEY_INPUT_EVENT                               :"KeyInput/Event"
//播放当前媒体
property string t_IPC_MEDIA_PLAY                                    :"Media/Play"
//暂停播放
property string t_IPC_MEDIA_PAUSE                                   :"Media/Pause"
//播放下一个媒体
property string t_IPC_MEDIA_NEXT                                    :"Media/Next"
//播放上一个媒体
property string t_IPC_MEDIA_PREVIOUS                                :"Media/Previous"
//接通电话
property string t_IPC_MEDIA_ANSWER_CALL                             :"Media/AnswerCall"
//挂断电话
property string t_IPC_MEDIA_HANGUP_CALL                             :"Media/HangupCall"
//小憩模式
property string t_IPC_C385_RESPITE_MODE                             :"C385/RespiteMode"
//小憩模式 Set 
property string t_IPC_C385_RESPITE_MODE_SET                         :"C385/RespiteMode/Set"
//露营模式
property string t_IPC_C385_CAMPING_MODE                             :"C385/CampingMode"
//露营模式 Set 
property string t_IPC_C385_CAMPING_MODE_SET                         :"C385/CampingMode/Set"
//召唤声开关
property string t_IPC_C385_CALLING_SOUND                            :"C385/CallingSound"
//召唤声开关 Set 
property string t_IPC_C385_CALLING_SOUND_SET                        :"C385/CallingSound/Set"
//召唤声风格
property string t_IPC_C385_CALLING_TYPE                             :"C385/CallingType"
//召唤声风格 Set 
property string t_IPC_C385_CALLING_TYPE_SET                         :"C385/CallingType/Set"
//电动出风口模式(智能风 自由风 扫风模式)
property string t_IPC_C385_ELECTRIC_AIR_OUTLET_MODE                 :"C385/ElectricAirOutletMode"
//燃料电池常温工作状态
property string t_IPC_C385_FCOPERATING_STATE                        :"C385/FCOperatingState"
//燃料电池低温工作状态
property string t_IPC_C385_FCOPERATING_STATE_LOW_TEMPERATURE        :"C385/FCOperatingStateLowTemperature"
//-A
property string t_IPC_AC_I_TMSAIR_OUT_SWT_STS1                      :"AC/iTMSAirOutSwtSts1"
}
