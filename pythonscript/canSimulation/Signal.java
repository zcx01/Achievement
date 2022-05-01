package mega.car;

import static mega.car.hardware.CarPropertyValue.MGR_ID_BIT_OFFSET;

import mega.car.annotation.DomainDefine;
import mega.car.annotation.PropertyDefine;
import mega.car.config.Extra;

@DomainDefine(
        domainId = Signal.MGR_ID,
        name = Extra.SERVICE_NAME,
        permission = Extra.PERMISSION)
public final class Signal {
    /**
     * @hide
     */
    public static final int MGR_ID = 100;

    /**
     * IACC/HWA工作模式
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:off
     *     0x1:standby
     *     0x2:passive
     *     0x3:active
     *     0x4:suspend
     *     0x5:prohibition
     *     0x6:reserved
     *     0x7:failure
     */
    @PropertyDefine(topic = "GW_31A/ACC_IACCHWAMode", type = Integer.class)
    public static final int GW_31A_ACC_IACCHWAMODE = MGR_ID << MGR_ID_BIT_OFFSET | 0x1;

    /**
     * ACC工作模式
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:OFF mode
     *     0x1:Passive mode
     *     0x2:StandBy mode
     *     0x3:Active Control mode
     *     0x4:Brake Only mode
     *     0x5:Override
     *     0x6:Stand Wait mode
     *     0x7:Failure mode
     */
    @PropertyDefine(topic = "GW_244/ACC_ACCMode", type = Integer.class)
    public static final int GW_244_ACC_ACCMODE = MGR_ID << MGR_ID_BIT_OFFSET | 0x2;

    /**
     * Handson请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no request
     *     0x1:level 1 request
     *     0x2:level 2 request
     *     0x3:level 3 request
     *     0x4:level 4 request
     *     0x5~0x7:reserved
     */
    @PropertyDefine(topic = "GW_31A/ACC_HandsOnReq", type = Integer.class)
    public static final int GW_31A_ACC_HANDSONREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x3;

    /**
     * 纵向接管请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no request
     *     0x1:level 1 request
     *     0x2:level 2 request
     *     0x3:reserved
     */
    @PropertyDefine(topic = "GW_307/ACC_LngTakeOverReq", type = Integer.class)
    public static final int GW_307_ACC_LNGTAKEOVERREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x4;

    /**
     * 横向接管请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no request
     *     0x1:level 1 request
     *     0x2:level 2 request
     *     0x3:reserved
     */
    @PropertyDefine(topic = "GW_31A/ACC_LatTakeoverReq", type = Integer.class)
    public static final int GW_31A_ACC_LATTAKEOVERREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x5;

    /**
     * 前碰撞预警提醒
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no warning
     *     0x1:warning
     */
    @PropertyDefine(topic = "GW_244/ACC_FCWPreWarning", type = Integer.class)
    public static final int GW_244_ACC_FCWPREWARNING = MGR_ID << MGR_ID_BIT_OFFSET | 0x6;

    /**
     * AWB激活
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:not Active
     *     0x1:Active
     */
    @PropertyDefine(topic = "GW_244/ACC_AWBActive", type = Integer.class)
    public static final int GW_244_ACC_AWBACTIVE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7;

    /**
     * AEB减速激活
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:not Active
     *     0x1:Active.
     */
    @PropertyDefine(topic = "GW_244/ACC_AEBActive", type = Integer.class)
    public static final int GW_244_ACC_AEBACTIVE = MGR_ID << MGR_ID_BIT_OFFSET | 0x8;

    /**
     * 后向左侧倒车横向预警报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No RCTA warning
     *     0x1:RCTA warning Level1
     *     0x2:RCTA warning Level2
     *     0x3:RCTA warning Level3
     */
    @PropertyDefine(topic = "GW_2A4/LCDAR_Left_RCTAAlert", type = Integer.class)
    public static final int GW_2A4_LCDAR_LEFT_RCTAALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0x9;

    /**
     * 后向右侧倒车横向预警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No RCTA warning
     *     0x1:RCTA warning Level1
     *     0x2:RCTA warning Level2
     *     0x3:RCTA warning Level3
     */
    @PropertyDefine(topic = "GW_2A4/LCDAR_RCTAAlert", type = Integer.class)
    public static final int GW_2A4_LCDAR_RCTAALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0xa;

    /**
     * 前向左侧横向预警报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No FCTA warning
     *     0x1:FCTA warning Level1
     *     0x2:FCTA warning Level2
     *     0x3:FCTA warning Level3
     */
    @PropertyDefine(topic = "GW_29E/ADS_FRC_Left_FCTALAlert", type = Integer.class)
    public static final int GW_29E_ADS_FRC_LEFT_FCTALALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0xb;

    /**
     * 前向右侧横向预警报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No FCTA warning
     *     0x1:FCTA warning Level1
     *     0x2:FCTA warning Level2
     *     0x3:FCTA warning Level3
     */
    @PropertyDefine(topic = "GW_29E/ADS_FRC_Right_FCTARAlert", type = Integer.class)
    public static final int GW_29E_ADS_FRC_RIGHT_FCTARALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0xc;

    /**
     * 加速踏板实际位置
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "VCU_2A1/VcuAccrPedlPosn", type = Float.class)
    public static final int VCU_2A1_VCUACCRPEDLPOSN = MGR_ID << MGR_ID_BIT_OFFSET | 0xd;

    /**
     * 加速踏板实际位置有效
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Valid
     *     0x1:Invalid
     */
    @PropertyDefine(topic = "VCU_2A1/VcuAccrPedlPosnVld", type = Integer.class)
    public static final int VCU_2A1_VCUACCRPEDLPOSNVLD = MGR_ID << MGR_ID_BIT_OFFSET | 0xe;

    /**
     * 前雨刮单次挂刷(一次挂刷开关状态)
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:OFF
     *     0x1:ON
     */
    @PropertyDefine(topic = "GW_384/BDC_FrtWipMistSW", type = Integer.class)
    public static final int GW_384_BDC_FRTWIPMISTSW = MGR_ID << MGR_ID_BIT_OFFSET | 0xf;

    /**
     * 人脸认证状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:未认证
     *     0x1:认证失败
     *     0x2:认证成功
     */
    @PropertyDefine(topic = "DMS_356/CDCFaceAuthentSts", type = Integer.class)
    public static final int DMS_356_CDCFACEAUTHENTSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x10;

    /**
     * 人脸账号管理反馈
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:执行成功
     *     0x1:执行失败
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceAccountFb", type = Integer.class)
    public static final int DMS_356_DMSFACEACCOUNTFB = MGR_ID << MGR_ID_BIT_OFFSET | 0x11;

    /**
     * 人脸数据ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xA:ID0~10
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceDataID", type = Integer.class)
    public static final int DMS_356_DMSFACEDATAID = MGR_ID << MGR_ID_BIT_OFFSET | 0x12;

    /**
     * 人脸认证声音提示请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:有请求
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceSoundWarn", type = Integer.class)
    public static final int DMS_356_DMSFACESOUNDWARN = MGR_ID << MGR_ID_BIT_OFFSET | 0x13;

    /**
     * 人脸认证语音提示请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:人脸认证成功
     *     0x2:人脸认证失败，请重试
     *     0x3:人脸尚未注册
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceAcoustWarn", type = Integer.class)
    public static final int DMS_356_DMSFACEACOUSTWARN = MGR_ID << MGR_ID_BIT_OFFSET | 0x14;

    /**
     * 人脸注册功能状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:激活
     *     0x1:退出激活
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceRegistFctSts", type = Integer.class)
    public static final int DMS_356_DMSFACEREGISTFCTSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x15;

    /**
     * 人脸注册文字提示请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:请保持正脸，不可佩戴墨镜、帽子、口罩等遮挡面部的物品
     *     0x2:操作超时
     *     0x3:刷脸失败次数过多，人脸注册失败，请稍后再试
     *     0x4:人脸注册成功
     *     0x5:人脸注册失败
     *     0x6:该账户已注册人脸信息，是否重新进行注册
     *     0x7:请靠紧靠背，正视前方
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceRegistDispReq", type = Integer.class)
    public static final int DMS_356_DMSFACEREGISTDISPREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x16;

    /**
     * 人脸注册声音提示请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:有请求
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceRegistSoundReq", type = Integer.class)
    public static final int DMS_356_DMSFACEREGISTSOUNDREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x17;

    /**
     * 人脸注册退出按键状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRegistExitSts", type = Integer.class)
    public static final int CDC_2D2_CDCFACEREGISTEXITSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x18;

    /**
     * 人脸注册再试一次按键状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRegistAgainSts", type = Integer.class)
    public static final int CDC_2D2_CDCFACEREGISTAGAINSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x19;

    /**
     * 人脸注册确定按键状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRegistOkSts", type = Integer.class)
    public static final int CDC_2D2_CDCFACEREGISTOKSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x1a;

    /**
     * 人脸账号管理请求
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:新增
     *     0x2:替换
     *     0x3:删除
     */
    @PropertyDefine(topic = "CDC_2D2/DmsFaceAccountReq", type = Integer.class)
    public static final int CDC_2D2_DMSFACEACCOUNTREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x1b;

    /**
     * 人脸账户管理ID
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xA:ID0~10
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceAccountID", type = Integer.class)
    public static final int CDC_2D2_CDCFACEACCOUNTID = MGR_ID << MGR_ID_BIT_OFFSET | 0x1c;

    /**
     * 当前登录账户人脸ID
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xA:ID0~10
     */
    @PropertyDefine(topic = "CDC_2D2/CdcCurrAccountFaceID", type = Integer.class)
    public static final int CDC_2D2_CDCCURRACCOUNTFACEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x1d;

    /**
     * 人脸注册请求
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:注册请求
     *     0x2:退出请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRegistReq", type = Integer.class)
    public static final int CDC_2D2_CDCFACEREGISTREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x1e;

    /**
     * 人脸识别否按键状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:有请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRecognizeNoSts", type = Integer.class)
    public static final int CDC_2D2_CDCFACERECOGNIZENOSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x1f;

    /**
     * 人脸识别是按键状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:无请求
     *     0x1:有请求
     */
    @PropertyDefine(topic = "CDC_2D2/CdcFaceRecognizeYesSts", type = Integer.class)
    public static final int CDC_2D2_CDCFACERECOGNIZEYESSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x20;

    /**
     * CDC_DVR SD卡错误状态
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no error（Sd卡无错误）
     *     0x1=no sdcard（Sd卡未挂载）
     *     0x2=sdcard error（Sd卡写错误）
     *     0x3=sdcard format error（Sd卡格式错误）
     *     0x4=sdcard insufficient（Sd卡容量不足）
     *     0x5=sdcard speed low（Sd卡速度过低）
     *     0x6=sdcard restoring(reserved)（Sd卡正在恢复文件）
     *     0x7=sdcard too large(Sd卡容量过大)
     */
    @PropertyDefine(topic = "CDC_3AF/CDC_DVR_SdcardErrorStatus", type = Integer.class)
    public static final int CDC_3AF_CDC_DVR_SDCARDERRORSTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x21;

    /**
     * CDC_DVR系统故障
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=normal
     *     0x1=error
     */
    @PropertyDefine(topic = "CDC_3AF/CDC_DVR_Error", type = Integer.class)
    public static final int CDC_3AF_CDC_DVR_ERROR = MGR_ID << MGR_ID_BIT_OFFSET | 0x22;

    /**
     * ACC紧急数据记录请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no request
     *     0x1:Event 1 Request
     *     0x2:Event 2 Request
     *     0x3:Image Record
     */
    @PropertyDefine(topic = "GW_244/ACC_EmergencyDataRrdReq", type = Integer.class)
    public static final int GW_244_ACC_EMERGENCYDATARRDREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x23;

    /**
     * 面部识别功能状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Disable 未激活
     *     0x1:Standby 待机
     *     0x2:Enable 激活
     */
    @PropertyDefine(topic = "DMS_356/DmsFaceDectSts", type = Integer.class)
    public static final int DMS_356_DMSFACEDECTSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x24;

    /**
     * 制动灯点亮请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Not request
     *     0x1:brake light ON
     *     0x2:Not used
     *     0x3:signal Not available
     */
    @PropertyDefine(topic = "VCU_2A1/VcuBrkLiOnReq", type = Integer.class)
    public static final int VCU_2A1_VCUBRKLIONREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x25;

    /**
     * AWB激活
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:not Active
     *     0x1:Active
     */
    @PropertyDefine(topic = "ADC_244/ACC_AWBActive", type = Integer.class)
    public static final int ADC_244_ACC_AWBACTIVE = MGR_ID << MGR_ID_BIT_OFFSET | 0x26;

    /**
     * 前碰撞预警提醒
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no warning
     *     0x1:warning
     */
    @PropertyDefine(topic = "ADC_244/ACC_FCWPreWarning", type = Integer.class)
    public static final int ADC_244_ACC_FCWPREWARNING = MGR_ID << MGR_ID_BIT_OFFSET | 0x27;

    /**
     * 驾驶辅助声音信息
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no voice
     *     0x1:latentWarning voive
     *     0x2:FCW/AEB voice
     *     0x3:ACC object detect voice
     *     0x4:ACC object disappeared voice
     *     0x5:ACC/IACC takeover request voice
     *     0x6:Lane Left dangerous warning  voice
     *     0x7:Lane Right dangerous warning  voice
     *     0x8:reserved
     *     0x9:IACC Active voice
     *     0xA:IACC exit voice
     *     0xB:reserved
     *     0xC:reserved
     *     0xD:cruise unintended exit
     *     0x0E:TrafficWarning
     *     0xF~0x1F:reserved
     */
    @PropertyDefine(topic = "ADC_31A/ACC_Voiceinfo", type = Integer.class)
    public static final int ADC_31A_ACC_VOICEINFO = MGR_ID << MGR_ID_BIT_OFFSET | 0x28;

    /**
     * 远光灯工作状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Off
     *     0x1:ON
     *     0x2:Not used
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "GW_288/BcmHiBeamSts", type = Integer.class)
    public static final int GW_288_BCMHIBEAMSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x29;

    /**
     * 近光灯工作状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Off
     *     0x1:ON
     *     0x2:Not used
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "GW_288/BcmLoBeamSts", type = Integer.class)
    public static final int GW_288_BCMLOBEAMSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x2a;

    /**
     * 左转向灯信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Off
     *     0x1:ON
     *     0x2:Not used
     *     0x3:Error
     */
    @PropertyDefine(topic = "GW_288/BcmTurnIndcrLe", type = Integer.class)
    public static final int GW_288_BCMTURNINDCRLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x2b;

    /**
     * 右转向灯信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Off
     *     0x1:ON
     *     0x2:Not used
     *     0x3:Error
     */
    @PropertyDefine(topic = "GW_288/BcmTurnIndcrRi", type = Integer.class)
    public static final int GW_288_BCMTURNINDCRRI = MGR_ID << MGR_ID_BIT_OFFSET | 0x2c;

    /**
     * 右侧盲点检测_换道辅助报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No LCA warning
     *     0x1:LCA warning level 1
     *     0x2:LCA warning level 2
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "ADC_2A4/LCDAR_BSD_LCAAlert", type = Integer.class)
    public static final int ADC_2A4_LCDAR_BSD_LCAALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0x2d;

    /**
     * 左侧盲点检测_换道辅助报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No LCA warning
     *     0x1:LCA warning level 1
     *     0x2:LCA warning level 2
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "ADC_2A4/LCDAR_Left_BSD_LCAAlert", type = Integer.class)
    public static final int ADC_2A4_LCDAR_LEFT_BSD_LCAALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0x2e;

    /**
     * 车道线方程系数C1
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_LaneEquationC1", type = Float.class)
    public static final int ADC_382_ACC_LANEEQUATIONC1 = MGR_ID << MGR_ID_BIT_OFFSET | 0x2f;

    /**
     * 车道线方程系数C2
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_LaneEquationC2", type = Float.class)
    public static final int ADC_382_ACC_LANEEQUATIONC2 = MGR_ID << MGR_ID_BIT_OFFSET | 0x30;

    /**
     * 车道线方程系数C3
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_LaneEquationC3", type = Float.class)
    public static final int ADC_382_ACC_LANEEQUATIONC3 = MGR_ID << MGR_ID_BIT_OFFSET | 0x31;

    /**
     * 前向左侧横向预警报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No FCTA warning
     *     0x1:FCTA warning Level1
     *     0x2:FCTA warning Level2
     *     0x3:FCTA warning Level3
     */
    @PropertyDefine(topic = "ADC_29E/ADS_FRC_Left_FCTALAlert", type = Integer.class)
    public static final int ADC_29E_ADS_FRC_LEFT_FCTALALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0x32;

    /**
     * 前向右侧横向预警报警信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No FCTA warning
     *     0x1:FCTA warning Level1
     *     0x2:FCTA warning Level2
     *     0x3:FCTA warning Level3
     */
    @PropertyDefine(topic = "ADC_29E/ADS_FRC_Right_FCTARAlert", type = Integer.class)
    public static final int ADC_29E_ADS_FRC_RIGHT_FCTARALERT = MGR_ID << MGR_ID_BIT_OFFSET | 0x33;

    /**
     * 轨迹显示状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no display
     *     0x1:LaneChangeTryPath，换道等待
     *     0x2:NormalLaneChangePath，换道过程
     *     0x3:LaneChangeReturnPath，换道回退
     *     0x4:CanNotChangeLanePath，换道等待或保持本车道行驶
     *     0x5:SmartBiasPath，智慧偏移路径
     *     0x6:FollowVehicleDrivePath，跟车行驶路径
     *     0x7:RecommendPath，规划路径
     */
    @PropertyDefine(topic = "ADC_36F/ADS_PathShow_Status", type = Integer.class)
    public static final int ADC_36F_ADS_PATHSHOW_STATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x34;

    /**
     * 距目标位置实时横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_312/ADS_ToTargetLatDistance", type = Float.class)
    public static final int ADC_312_ADS_TOTARGETLATDISTANCE = MGR_ID << MGR_ID_BIT_OFFSET | 0x35;

    /**
     * 安全距离提醒报警
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no warning
     *     0x1:warning
     */
    @PropertyDefine(topic = "ADC_244/ACC_FCWLatentWarning", type = Integer.class)
    public static final int ADC_244_ACC_FCWLATENTWARNING = MGR_ID << MGR_ID_BIT_OFFSET | 0x36;

    /**
     * 目标1的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1Detection", type = Integer.class)
    public static final int ADC_382_ACC_TARGET1DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x37;

    /**
     * 目标1的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1ID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET1ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x38;

    /**
     * 目标1的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no display
     *     0x1:sedan
     *     0x2:motorcycle
     *     0x3:pedestrian
     *     0x4:Bicycle
     *     0x5:Bus
     *     0x7:truck
     *     0x8:Cone Consideration
     *     0x9:Warning Column
     *     0xA:Water Horse
     *     0xB:Anti-Collision Bucket
     *     0xC:others
     *     0xD:animal
     *     0xE:Non-road vehicle
     *     0xF:This car
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1Type", type = Integer.class)
    public static final int ADC_382_ACC_TARGET1TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x39;

    /**
     * 目标1的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1LngRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET1LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x3a;

    /**
     * 目标1的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1LatRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET1LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x3b;

    /**
     * 目标1的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1Direction", type = Integer.class)
    public static final int ADC_382_ACC_TARGET1DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x3c;

    /**
     * 目标1的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1HeadingAngle", type = Float.class)
    public static final int ADC_382_ACC_TARGET1HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x3d;

    /**
     * 目标1的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target1ZoneID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET1ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x3e;

    /**
     * 目标2的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2Detection", type = Integer.class)
    public static final int ADC_382_ACC_TARGET2DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x3f;

    /**
     * 目标2的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2ID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET2ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x40;

    /**
     * 目标2的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2Type", type = Integer.class)
    public static final int ADC_382_ACC_TARGET2TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x41;

    /**
     * 目标2的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2LngRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET2LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x42;

    /**
     * 目标2的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2LatRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET2LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x43;

    /**
     * 目标2的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2Direction", type = Integer.class)
    public static final int ADC_382_ACC_TARGET2DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x44;

    /**
     * 目标2的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2HeadingAngle", type = Float.class)
    public static final int ADC_382_ACC_TARGET2HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x45;

    /**
     * 目标2的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target2ZoneID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET2ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x46;

    /**
     * 目标3的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3Detection", type = Integer.class)
    public static final int ADC_382_ACC_TARGET3DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x47;

    /**
     * 目标3的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3ID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET3ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x48;

    /**
     * 目标3的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3Type", type = Integer.class)
    public static final int ADC_382_ACC_TARGET3TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x49;

    /**
     * 目标3的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3LngRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET3LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x4a;

    /**
     * 目标3的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3LatRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET3LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x4b;

    /**
     * 目标3的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3Direction", type = Integer.class)
    public static final int ADC_382_ACC_TARGET3DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x4c;

    /**
     * 目标3的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3HeadingAngle", type = Float.class)
    public static final int ADC_382_ACC_TARGET3HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x4d;

    /**
     * 目标3的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target3ZoneID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET3ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x4e;

    /**
     * 目标4的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4Detection", type = Integer.class)
    public static final int ADC_382_ACC_TARGET4DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x4f;

    /**
     * 目标4的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4ID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET4ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x50;

    /**
     * 目标4的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4Type", type = Integer.class)
    public static final int ADC_382_ACC_TARGET4TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x51;

    /**
     * 目标4的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4LngRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET4LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x52;

    /**
     * 目标4的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4LatRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET4LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x53;

    /**
     * 目标4的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4Direction", type = Integer.class)
    public static final int ADC_382_ACC_TARGET4DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x54;

    /**
     * 目标4的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4HeadingAngle", type = Float.class)
    public static final int ADC_382_ACC_TARGET4HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x55;

    /**
     * 目标4的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target4ZoneID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET4ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x56;

    /**
     * 目标5的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5Detection", type = Integer.class)
    public static final int ADC_382_ACC_TARGET5DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x57;

    /**
     * 目标5的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5ID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET5ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x58;

    /**
     * 目标5的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5Type", type = Integer.class)
    public static final int ADC_382_ACC_TARGET5TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x59;

    /**
     * 目标5的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5LngRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET5LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x5a;

    /**
     * 目标5的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5LatRange", type = Float.class)
    public static final int ADC_382_ACC_TARGET5LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x5b;

    /**
     * 目标5的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5Direction", type = Integer.class)
    public static final int ADC_382_ACC_TARGET5DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x5c;

    /**
     * 目标5的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5HeadingAngle", type = Float.class)
    public static final int ADC_382_ACC_TARGET5HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x5d;

    /**
     * 目标5的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_382/ACC_Target5ZoneID", type = Integer.class)
    public static final int ADC_382_ACC_TARGET5ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x5e;

    /**
     * 目标6的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6Detection", type = Integer.class)
    public static final int ADC_307_ACC_TARGET6DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x5f;

    /**
     * 目标6的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6ID", type = Integer.class)
    public static final int ADC_307_ACC_TARGET6ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x60;

    /**
     * 目标6的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6Type", type = Integer.class)
    public static final int ADC_307_ACC_TARGET6TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x61;

    /**
     * 目标6的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6LngRange", type = Float.class)
    public static final int ADC_307_ACC_TARGET6LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x62;

    /**
     * 目标6的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6LatRange", type = Float.class)
    public static final int ADC_307_ACC_TARGET6LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x63;

    /**
     * 目标6的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6Direction", type = Integer.class)
    public static final int ADC_307_ACC_TARGET6DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x64;

    /**
     * 目标6的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6HeadingAngle", type = Float.class)
    public static final int ADC_307_ACC_TARGET6HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x65;

    /**
     * 目标6的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target6ZoneID", type = Integer.class)
    public static final int ADC_307_ACC_TARGET6ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x66;

    /**
     * 目标7的识别情况
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=not dectected
     *     0x1=IP display
     *     0x2=Front Target
     *     0x3=IACC target
     *     0x4=AEB target
     *     0x5=dangerous target（ELK、UDLC、RCW, etc）
     *     0x6=other target
     *     0x7=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7Detection", type = Integer.class)
    public static final int ADC_307_ACC_TARGET7DETECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x67;

    /**
     * 目标7的ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x3F
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7ID", type = Integer.class)
    public static final int ADC_307_ACC_TARGET7ID = MGR_ID << MGR_ID_BIT_OFFSET | 0x68;

    /**
     * 目标7的类型
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=sedan
     *     0x2=motorcycle
     *     0x3=pedestrian
     *     0x4=Bicycle
     *     0x5=Bus
     *     0x7=truck
     *     0x8=Cone Consideration
     *     0x9=Warning Column
     *     0xA=Water Horse
     *     0xB=Anti-Collision Bucket
     *     0xC=others
     *     0xD-0xF=Rev
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7Type", type = Integer.class)
    public static final int ADC_307_ACC_TARGET7TYPE = MGR_ID << MGR_ID_BIT_OFFSET | 0x69;

    /**
     * 目标7的纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0~0xFA0=-100~300
     *     0xFA1~0xFFE=reserved
     *     0xFFF=Invalid
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7LngRange", type = Float.class)
    public static final int ADC_307_ACC_TARGET7LNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x6a;

    /**
     * 目标7的横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     向左为正，向右为负
     *     0x0-0x3E8：-50-50m
     *     0x3E9-0x3FE：reserved
     *     0x3FF=Invalid
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7LatRange", type = Float.class)
    public static final int ADC_307_ACC_TARGET7LATRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x6b;

    /**
     * 目标7的方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Forward
     *     0x1=OnComing
     *     0x2=Left
     *     0x3=Right
     *     0x4=unknown
     *     0x5=refer to headingangle
     *     0x6-0x7=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7Direction", type = Integer.class)
    public static final int ADC_307_ACC_TARGET7DIRECTION = MGR_ID << MGR_ID_BIT_OFFSET | 0x6c;

    /**
     * 目标7的航向角
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7HeadingAngle", type = Float.class)
    public static final int ADC_307_ACC_TARGET7HEADINGANGLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x6d;

    /**
     * 目标7的区域ID
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no zoneid
     *     0x1-0xB=zoneid1-11
     *     0xC=hostlane_zone
     *     0xD=leftlane_zone
     *     0xE=rightlane_zone
     *     0xF=LLLane_zone
     *     0x10=RRLane_zone
     *     0x11=Ramp_zone
     *     0x12=others
     *     0x13-0x1F=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_Target7ZoneID", type = Integer.class)
    public static final int ADC_307_ACC_TARGET7ZONEID = MGR_ID << MGR_ID_BIT_OFFSET | 0x6e;

    /**
     * 车辆中心到左左侧车道线的距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0xF0=0-12
     *     0xF1-0xFF=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_LLLaneDis", type = Float.class)
    public static final int ADC_307_ACC_LLLANEDIS = MGR_ID << MGR_ID_BIT_OFFSET | 0x6f;

    /**
     * 车辆中心到右右侧车道线的距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0xF0=-12-0
     *     0xF1-0xFF=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_RRLaneDis", type = Float.class)
    public static final int ADC_307_ACC_RRLANEDIS = MGR_ID << MGR_ID_BIT_OFFSET | 0x70;

    /**
     * 车辆中心到左侧车道线的距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x78=-1-5
     *     0x79-0x7F=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_LLaneDistanceFus", type = Float.class)
    public static final int ADC_307_ACC_LLANEDISTANCEFUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x71;

    /**
     * 车辆中心到右侧车道线的距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0-0x78=-5-1
     *     0x78-0x7F=reserved
     */
    @PropertyDefine(topic = "ADC_307/ACC_RLaneDistanceFus", type = Float.class)
    public static final int ADC_307_ACC_RLANEDISTANCEFUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x72;
}
