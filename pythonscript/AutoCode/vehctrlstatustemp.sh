#!/bin/bash

AutoCode vehctrl_status air_conditioner_status  signal top 空调设置反馈状态

//前排风量档位
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsFrntWindLvl_g,TOPIC_VEHCTRL_STS_TMS_FRNT_WIND_LVL);

//前出风模式
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsFrntBlowMod_g,TOPIC_VEHCTRL_STS_TMS_FRNT_BLOW_MOD); 

//主驾温度值
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsDrvrAutT_g,TOPIC_VEHCTRL_STS_TMS_DRVR_AUT_T); 

//副驾温度值
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsPassAutT_g,TOPIC_VEHCTRL_STS_TMS_PASS_AUT_T);

//空调工作状态
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsAcOnOffSts_g,TOPIC_VEHCTRL_STS_TMS_AC_ON_OFF_STS); 

//前除霜状态
air_conditioner_status->addSignalAndTop(&CANSIG_CDC_2D2__CdcFrntDefrosterSet_g,TOPIC_VEHCTRL_STS_TMS_FRNT_DEFROSTER);

//后除霜工作状态
air_conditioner_status->addSignalAndTop(&CANSIG_CDC_2D2__CdcReDefrosterSet_g,TOPIC_VEHCTRL_STS_BCM_REAR_DEFROSTERSTATUS); 

//循环模式状态
air_conditioner_status->addSignalAndTop(&CANSIG_CDC_2D2__CdcCycModSet_g,TOPIC_VEHCTRL_STS_TMS_CYC_MOD);

//最大制冷状态
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsMaxAcSts_g,TOPIC_VEHCTRL_STS_TMS_MAX_AC_STS);

#AutoCode vehctrl_status 前排空调自动模式状态

//HEAT状态
air_conditioner_status->addSignalAndTop(&CANSIG_GW_2A8__TmsHeatSts_g,TOPIC_VEHCTRL_STS_TMS_HEAT_STS); 
