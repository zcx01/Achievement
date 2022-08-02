package mega.car;

import static mega.car.hardware.CarPropertyValue.MGR_ID_BIT_OFFSET;

import mega.car.annotation.DomainDefine;
import mega.car.annotation.PropertyDefine;
import mega.car.config.Extra;

@DomainDefine(
        domainId = Signal.MGR_ID,
        name = Extra.SERVICE_NAME,
        permission = Extra.PERMISSION)
@SuppressWarnings("LineLength")
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

    /**
     * DDSAS功能开关请求
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Inactive
     *     0x1:Off
     *     0x2:On
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_DDSAS_Enable", type = Integer.class)
    public static final int CDC_507_HU_DDSAS_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x73;

    /**
     * DDSAS功能开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Disable（默认）
     *     0x1:Enable
     */
    @PropertyDefine(topic = "ADC_307/ADS_DDSAS_Enable", type = Integer.class)
    public static final int ADC_307_ADS_DDSAS_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x74;

    /**
     * 陪伴助手设置开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:inactive
     *     0x1:off
     *     0x2:on
     *     0x3:reserve
     */
    @PropertyDefine(topic = "CDC_507/HU_CompanionAssitModeEnable", type = Integer.class)
    public static final int CDC_507_HU_COMPANIONASSITMODEENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x75;

    /**
     * 陪伴助手设置开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:off
     *     0x1:on（默认）
     */
    @PropertyDefine(topic = "ADC_31A/ADC_CompanionAssitModeEnable", type = Integer.class)
    public static final int ADC_31A_ADC_COMPANIONASSITMODEENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x76;

    /**
     * 智能泊车辅助开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Inactive
     *     0x1:Off
     *     0x2:On
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_Parking_Asistant_Syste_Enable", type = Integer.class)
    public static final int CDC_507_HU_PARKING_ASISTANT_SYSTE_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x77;

    /**
     * 智能泊车辅助开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Disable（默认）
     *     0x1:Enable
     */
    @PropertyDefine(topic = "ADC_307/ADS_Parking_Asistant_Syste_Enable", type = Integer.class)
    public static final int ADC_307_ADS_PARKING_ASISTANT_SYSTE_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x78;

    /**
     * 代客泊车辅助开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Inactive
     *     0x1:Off
     *     0x2:On
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_Automated_Valet_Parking_Enable", type = Integer.class)
    public static final int CDC_507_HU_AUTOMATED_VALET_PARKING_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x79;

    /**
     * 代客泊车辅助开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Disable（默认）
     *     0x1:Enable
     */
    @PropertyDefine(topic = "ADC_307/ADS_Automated_Valet_Parking_Enable", type = Integer.class)
    public static final int ADC_307_ADS_AUTOMATED_VALET_PARKING_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7a;

    /**
     * 新手模式辅助开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Inactive
     *     0x1:Off
     *     0x2:On
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_Novice_Enable", type = Integer.class)
    public static final int CDC_507_HU_NOVICE_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7b;

    /**
     * 新手模式辅助开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Disable（默认）
     *     0x1:Enable
     */
    @PropertyDefine(topic = "ADC_307/ADS_Novice_Enable", type = Integer.class)
    public static final int ADC_307_ADS_NOVICE_ENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7c;

    /**
     * 开门预警开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:inactive
     *     0x1:Off
     *     0x2:On
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_SEAEnable", type = Integer.class)
    public static final int CDC_507_HU_SEAENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7d;

    /**
     * 开门预警使能状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Off
     *     0x1:On
     */
    @PropertyDefine(topic = "GW_2AD/LCDAL_SEAEnableStatus", type = Integer.class)
    public static final int GW_2AD_LCDAL_SEAENABLESTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x7e;

    /**
     * 换道驾驶风格
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Inactive
     *     0x1:ComfortableStyle
     *     0x2:SportStyle
     *     0x3~0x7:reserve
     */
    @PropertyDefine(topic = "CDC_507/HU_LaneChangeStyle", type = Integer.class)
    public static final int CDC_507_HU_LANECHANGESTYLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x7f;

    /**
     * 换道驾驶风格状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:ComfortableStyle（默认值）
     *     0x1:SportStyle
     *     0x2:reserve
     *     0x3:reserve
     */
    @PropertyDefine(topic = "ADC_312/ADS_LaneChangeStyle", type = Integer.class)
    public static final int ADC_312_ADS_LANECHANGESTYLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x80;

    /**
     * NDA语音提示开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0 =Inactive
     *     0x1 =Off
     *     0x2=On
     *       0x3= Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_NDAAudioWarEnable", type = Integer.class)
    public static final int CDC_507_HU_NDAAUDIOWARENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x81;

    /**
     * 智慧换道提示开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Inactive
     *     0x1=Off
     *     0x2=On
     *       0x3= Reserved
     */
    @PropertyDefine(topic = "CDC_394/HU_ADSLaneChangeVoiceEnable", type = Integer.class)
    public static final int CDC_394_HU_ADSLANECHANGEVOICEENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x82;

    /**
     * 安全报警提示开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0 =Inactive
     *     0x1 =Off
     *     0x2=On
     *       0x3= Reserved
     */
    @PropertyDefine(topic = "CDC_394/HU_ADSSafeVoiceEnable", type = Integer.class)
    public static final int CDC_394_HU_ADSSAFEVOICEENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x83;

    /**
     * 路况播报提示开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0 =Inactive
     *     0x1=Off
     *     0x2=On
     *       0x3= Reserved
     */
    @PropertyDefine(topic = "CDC_394/HU_ADSRoadVoiceEnable", type = Integer.class)
    public static final int CDC_394_HU_ADSROADVOICEENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x84;

    /**
     * NDA语音提示开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=OFF
     *     0x1=ON
     */
    @PropertyDefine(topic = "GW_312/ADS_NDAAudioWarEnableStatus", type = Integer.class)
    public static final int GW_312_ADS_NDAAUDIOWARENABLESTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x85;

    /**
     * 安全报警提示开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=OFF
     *     0x1=ON
     */
    @PropertyDefine(topic = "GW_312/ADS_ADSSafeVoiceEnableSts", type = Integer.class)
    public static final int GW_312_ADS_ADSSAFEVOICEENABLESTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x86;

    /**
     * 智慧换道提示开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=OFF
     *     0x1=ON
     */
    @PropertyDefine(topic = "GW_312/ADS_ADSLaneChangeVoiceEnableSts", type = Integer.class)
    public static final int GW_312_ADS_ADSLANECHANGEVOICEENABLESTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x87;

    /**
     * 路况播报提示开关状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=OFF
     *     0x1=ON
     */
    @PropertyDefine(topic = "GW_312/ADS_ADSRoadVoiceEnableSts", type = Integer.class)
    public static final int GW_312_ADS_ADSROADVOICEENABLESTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x88;

    /**
     * 抽烟空调开启请求
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No Request
     *     0x1:Request
     */
    @PropertyDefine(topic = "CDC_356/CdcSmokeACStartReq", type = Integer.class)
    public static final int CDC_356_CDCSMOKEACSTARTREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x89;

    /**
     * 抽烟外循环开启请求
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:No request
     *     0x1:Request
     */
    @PropertyDefine(topic = "CDC_356/CdcSmokeOuterCircReq", type = Integer.class)
    public static final int CDC_356_CDCSMOKEOUTERCIRCREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x8a;

    /**
     * 预约加热请求
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Not request
     *     0x1:校时请求
     *     0x2:预热请求
     *     0x3:reserved
     */
    @PropertyDefine(topic = "TBOX_2F7/TboxHeatReq", type = Integer.class)
    public static final int TBOX_2F7_TBOXHEATREQ = MGR_ID << MGR_ID_BIT_OFFSET | 0x8b;

    /**
     * 新手模式语音
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:IDLE
     *     0x1:Educating Inroduction
     *     0x2:Cancel Feedback
     *     0x3:Recommended for beginners
     *     0x4:activate any time
     *     0x5:perfect completion
     *     0x6:first Educating
     *     0x7:intelligent parking
     *     0x8:control speed
     *     0x9:slow down
     *     0xA:find slot
     *     0xB:Parking Modeselection
     *     0xC:slot too small
     *     0xD:APP parking
     *     0xE:Relese brake&steer
     *     0xF:relax
     *     0x10:close door
     *     0x11:chose auto mode
     *     0x12:Relese ACCpedal
     *     0x13:keep shift
     *     0x14:relese EPB
     *     0x15:object cut in
     *     0x16:parking Success
     *     0x17:system cancel
     *     0x18：time cancel
     *     0x19：steer cancel
     *     0x1A:gear cancel
     *     0x1B:pedal cancel
     *     0x1C:direction chose
     *     0x1D：direction&left light
     *     0x1E:direction&right light
     *     0x1F:welcome
     *     0x20:guide you
     *     0x21:open set
     *     0x22:AVM
     *     0x23:chose slot
     *     0x24:chose mode
     *     0x25:close guide
     *     0x26:click select direction
     *     0x27-7F:Reserved
     */
    @PropertyDefine(topic = "ADC_31E/APA_Voice_Notice", type = Integer.class)
    public static final int ADC_31E_APA_VOICE_NOTICE = MGR_ID << MGR_ID_BIT_OFFSET | 0x8c;

    /**
     * ACC目标巡航车速
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_307/ACC_SetSpeed", type = Integer.class)
    public static final int GW_307_ACC_SETSPEED = MGR_ID << MGR_ID_BIT_OFFSET | 0x8d;

    /**
     * 匝道距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_36F/ADS_DisToRamp", type = Integer.class)
    public static final int GW_36F_ADS_DISTORAMP = MGR_ID << MGR_ID_BIT_OFFSET | 0x8e;

    /**
     * 轨迹显示C1
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_36F/ADS_PathShow_C1", type = Float.class)
    public static final int GW_36F_ADS_PATHSHOW_C1 = MGR_ID << MGR_ID_BIT_OFFSET | 0x8f;

    /**
     * 轨迹显示C2
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_36F/ADS_PathShow_C2", type = Float.class)
    public static final int GW_36F_ADS_PATHSHOW_C2 = MGR_ID << MGR_ID_BIT_OFFSET | 0x90;

    /**
     * 轨迹显示C3
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_36F/ADS_PathShow_C3", type = Float.class)
    public static final int GW_36F_ADS_PATHSHOW_C3 = MGR_ID << MGR_ID_BIT_OFFSET | 0x91;

    /**
     * 轨迹显示纵向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_36F/ADS_PathShowLngRange", type = Integer.class)
    public static final int GW_36F_ADS_PATHSHOWLNGRANGE = MGR_ID << MGR_ID_BIT_OFFSET | 0x92;

    /**
     * 匝道信息
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:notThroughRamp
     *     0x1:throughRamp
     *     0x2:invalid
     *     0x3:reserved
     */
    @PropertyDefine(topic = "GW_36F/ADS_PathThroughRamp", type = Integer.class)
    public static final int GW_36F_ADS_PATHTHROUGHRAMP = MGR_ID << MGR_ID_BIT_OFFSET | 0x93;

    /**
     * 匝道方向
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:invalid
     *     0x1:onRightSide
     *     0x2:onLeftSide
     *     0x3:reserved
     */
    @PropertyDefine(topic = "GW_36F/ADS_RampSide", type = Integer.class)
    public static final int GW_36F_ADS_RAMPSIDE = MGR_ID << MGR_ID_BIT_OFFSET | 0x94;

    /**
     * 匝道状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:no display
     *     0x1:nearRamp
     *     0x2:rampIn
     *     0x3:inRamp
     *     0x4:RampOut
     *     0x5-0x7:reserved
     */
    @PropertyDefine(topic = "GW_36F/ADS_RampStatus", type = Integer.class)
    public static final int GW_36F_ADS_RAMPSTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x95;

    /**
     * 距目标位置实时横向距离
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_312/ADS_ToTargetLatDistance", type = Float.class)
    public static final int GW_312_ADS_TOTARGETLATDISTANCE = MGR_ID << MGR_ID_BIT_OFFSET | 0x96;

    /**
     * NDA设定车速模式状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=invalid
     *     0x1=Manual/Normal
     *     0x2=Auto/Sport
     *     0x3=Auto/Eco
     */
    @PropertyDefine(topic = "GW_36F/ADS_NDASetSpdModeStatus", type = Integer.class)
    public static final int GW_36F_ADS_NDASETSPDMODESTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x97;

    /**
     * NDA导航开关
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0 =Inactive
     *     0x1 =Off
     *     0x2=On
     *       0x3= Reserved
     */
    @PropertyDefine(topic = "CDC_507/HU_NDANavEnable", type = Integer.class)
    public static final int CDC_507_HU_NDANAVENABLE = MGR_ID << MGR_ID_BIT_OFFSET | 0x98;

    /**
     * NDA设定车速模式
     * <br/>
     * Attribute: <br/>
     * {access, WRITE} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=Inactive
     *     0x1=Manual/Normal
     *     0x2=Auto/Sport
     *     0x3=Auto/Eco
     */
    @PropertyDefine(topic = "CDC_507/HU_NDASetSpdMode", type = Integer.class)
    public static final int CDC_507_HU_NDASETSPDMODE = MGR_ID << MGR_ID_BIT_OFFSET | 0x99;

    /**
     * NDA状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=OFF
     *     0x1=Passive
     *     0x2=StandBy
     *     0x3=ALC Active
     *     0x4=FIDA Active
     *     0x5=Takeover
     *     0x6=Prohibition
     *     0x7~0xF=Reserved
     */
    @PropertyDefine(topic = "GW_36F/ADS_NDAStatus", type = Integer.class)
    public static final int GW_36F_ADS_NDASTATUS = MGR_ID << MGR_ID_BIT_OFFSET | 0x9a;

    /**
     * NDA提示信息
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0=no display
     *     0x1=Out of Road ODD
     *     0x2=NDA Limit
     *     0x3=Weather Limit
     *     0x4=Turn Limit
     *     0x5=System Limit
     *     0x6=Toll Exit
     *     0x7=TrafficAccident Exit
     *     0x8=Construction Exit
     *     0x9=Imminent
     *     xit
     *     0xA=Handsoff And Eyesoff
     *     0xB=Eyesoff level2
     *     0xC=Eyesoff level1
     *     0xD=About Exitt
     *     0xE=Sharp Turn
     *     0xF=Leave current road
     *     0x10=Join to main road
     *     0x11=Speed too high
     *     0x12~0x1F=reserved
     */
    @PropertyDefine(topic = "GW_36F/ADS_NDATextInfo", type = Integer.class)
    public static final int GW_36F_ADS_NDATEXTINFO = MGR_ID << MGR_ID_BIT_OFFSET | 0x9b;

    /**
     * 智能驾驶信息
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x1=ACC:ACC is OFF
     *     0x2=ACC:ACC system error
     *     0x3=ACC:ACC Error by EMS/VCU/TCU
     *     0x4=ACC:ACC Error by EPBI
     *     0x5=ACC:SAS Error
     *     0x6=ACC:Button Error
     *     0x7=ACC:IP Fail
     *     0x8=ACC:ACC temporary unavailable by others
     *     0x9=ACC:ACC error by Front Camera
     *     0xA=ACC:ACC error by Front Radar
     *     0xB=ACC:Engine No Running
     *     0xC=ACC:door is open
     *     0xD=ACC:bonnet is Open
     *     0xE=ACC:Trunk is Open
     *     0xF=ACC:Tire Status is abnormal
     *     0x10=ACC:Bad weather
     *     0x11=ACC:Seatbelt unbuckled
     *     0x12=ACC:ESP off
     *     0x13=ACC:No forward gear
     *     0x14=ACC:APA  is on
     *     0x15=ACC:EPB activate
     *     0x16=ACC:ACC cannot active by snow mode
     *     0x17=ACC:SteeringAngle is over
     *     0x18=ACC:brake pedal is applied
     *     0x19=ACC:Speed over 150kph
     *     0x1A=ACC:caution about driving safty
     *     0x1B=ACC:Road wet and slippery
     *     0x1C=ACC:Road bumpy
     *     0x1D=ACC:Have Pedestrain or Riders
     *     0x1E=ACC:Out of slope or curvature range
     *     0x1F=ACC:ACC active control is cancelled
     *     0x20=ACC:ACC cannot active by Race mode
     *     0x21=ACC:ACC unintended exit warning
     *     0x22=ACC:emergency brake suddenly
     *     0x23=ACC:speed reduce by condition
     *     0x24=ACC:speed reduce by ramp
     *     0x25=ACC:speed reduce by SpdLimited
     *     0x26=ACC:speed reduce by Tollstation
     *     0x27=ACC:speed reduce by tunnel
     *     0x28=ACC:unable to activate ACC
     *     0x29=ACC:车辆起步提醒（前车驶离）
     *     0x2A=ACC:激活成功提醒
     *     0x2B=ACC:前方红绿灯-智能限速
     *     0x2C=ACC:前方人行横道-请注意减速慢行
     *     0x2D=ACC:前方人行横道-智能限速
     *     0x2E=ACC:前方收费站-请注意减速慢行
     *     0x2F=ACC:前方收费站-智能限速
     *     0x30=ACC:前方弯道-智能限速
     *     0x31=ACC:前雷达不可用-ACC退出
     *     0x32=ACC:前摄像头不可用-ACC退出
     *     0x33=ACC:推荐调节巡航车速-避让并行车辆
     *     0x34=ACC:巡航驻车提醒
     *     0x35=ACC:雨天道路湿滑-自动增加跟车时距
     *     0x36=ACC:智能加速避让并行车辆
     *     0x37=ACC:智能减速避让并行车辆
     *     0x38=ACC:主动提速提醒
     *     0x39=ACC:主动退出提醒（稍强）
     *     0x3A=ACC:自适应巡航已恢复
     *     0x3B=ACC:操作反馈-设定车速达到上限
     *     0x3C=ACC:操作反馈-设定车速达到下限
     *     0x3D=ACC:操作反馈-设定车速达到限速值
     *     0x3E=ACC:操作反馈-超速接近纵向控制极限，即将退出
     *     0x3F-0x64预留
     *     0x65=IACC:IACC not available by EPS
     *     0x66=IACC:longitudinal control not available
     *     0x67=IACC:ADR/DVR Status not Match
     *     0x68=IACC:other system error
     *     0x69=IACC:prohibition request for safestop
     *     0x6A=IACC:Please turn on IACC in incall
     *     0x6B=IACC:Driver Drowsy or Distracted
     *     0x6C=IACC:SteeringAngle is over
     *     0x6D=IACC:exceed speed limit
     *     0x6E=IACC:turn light switch on
     *     0x6F=IACC:turn light switch on
     *     0x70=IACC:driver overrides steering
     *     0x71=IACC:caution about driving safty
     *     0x72=IACC:unable to active for not in lane/crossing lane
     *     0x73=IACC:lane condition not available
     *     0x74=IACC:unable to active in curve
     *     0x75=IACC:unable to active in Bad weather
     *     0x76=IACC:system error
     *     0x77=IACC:LKA Takeover Req
     *     0x78=IACC:ELK active
     *     0x79=IACC:HeadingAngle is over
     *     0x7A=IACC:LAT invalid
     *     0x7B=IACC:LAT invalid（in safety stargy)
     *     0x7C=IACC:Hands on plz
     *     0x7D=IACC:IACC active
     *     0x7E=IACC:IACC Cancel
     *     0x7F=IACC:IACC deactivate
     *     0x80=IACC:iacc override
     *     0x81=IACC:IACC unintended exit
     *     0x82=IACC:Lights on please
     *     0x83=IACC:Longitude Exit
     *     0x84=IACC:Prohibition request for rdf
     *     0x85=IACC:takeover request with safety stop completed
     *     0x86=IACC:takeover request with safety stoping
     *     0x87=IACC:unable to activate IACC
     *     0x88=IACC:未认证用户使用智能驾驶功能提醒
     *     0x89=IACC:超速接近横向控制的极限即将退出
     *     0x8A=IACC:车辆临时靠左行驶，避让并行车辆
     *     0x8B=IACC:车辆临时靠右行驶，避让并行车辆
     *     0x8C=IACC:车辆临时靠左行驶，避让护栏
     *     0x8D=IACC:车辆临时靠右行驶，避让护栏
     *     0x8E-0xC8预留
     *     0xC9=UDLC:UDLC exit，触发式换道已退出，（UDLC不再等待换道并且不再主导控制）
     *     0xCA=UDLC:UDLC return，触发式换道回退原车道（驾驶员取消换道而回退）
     *     0xCB=UDLC:UDLC finished，请拨回转向灯（换道完成或回退对中完成时）
     *     0xCC=UDLC:前方道路汇流，推荐换道行驶
     *     0xCD=UDLC:change lane  to both sides for the  traffic jam,两边车道均可支持变道
     *     0xCE=UDLC:Lane change request by ramp
     *     0xCF=UDLC:change lane  to left side for the  traffic jam,左边车道可支持变道
     *     0xD0=UDLC:change lane  to right side for the  traffic jam,右边车道可支持变道
     *     0xD1=UDLC:out of ODD暂时不满足换道条件，不尝试换道
     *     0xD2=UDLC:Please turn on the UDLC in HU请在主机中打开主动换道设置开关
     *     0xD3=UDLC:speed out of range车速超出范围，自动换道条件不满足
     *     0xD4=UDLC:UDLC System Error自动换道系统故障
     *     0xD5=UDLC:雨量过大，自动换道条件不满足
     *     0xD6=UDLC:wait over time,换道尝试超时中止
     *     0xD7=UDLC:推荐向左换道-道路更畅通
     *     0xD8=UDLC:推荐向左换道-超越前车
     *     0xD9=UDLC:推荐向左换道-避让前方障碍物
     *     0xDA=UDLC:推荐向左换道-避让前方异常车辆
     *     0xDB=UDLC:推荐向左换道-道路前方有道路施工
     *     0xDC=UDLC:推荐向左换道-提前避让右侧汇入车辆
     *     0xDD=UDLC:推荐向左换道-避让右侧汇入车辆
     *     0xDE=UDLC:推荐向左换道-前方道路即将向左合并
     *     0xDF=UDLC:推荐向左换道-避让右侧大型车辆
     *     0xE0=UDLC:推荐向左换道-避让后方大型车辆
     *     0xE1=UDLC:推荐向右换道-道路更畅通
     *     0xE2=UDLC:推荐向右换道-超越前车
     *     0xE3=UDLC:推荐向右换道-道路前方有障碍物
     *     0xE4=UDLC:推荐向右换道-道路前方有异常车辆
     *     0xE5=UDLC:推荐向右换道-道路前方有道路施工
     *     0xE6=UDLC:推荐向右换道-提前避让左侧汇入车辆
     *     0xE7=UDLC:推荐向右换道-避让左侧汇入车辆
     *     0xE8=UDLC:推荐向右换道-前方道路即将向右合并
     *     0xE9=UDLC:推荐向右换道-避让左侧大型车辆
     *     0xEA=UDLC:推荐向右换道-避让后方大型车辆
     *     0xEB=UDLC:避让侧后方来车，返回原车道
     *     0xEC=UDLC:避让危险车辆，返回原车道
     *     0xED=UDLC:避让行人，返回原车道
     *     0xEE=UDLC:避让障碍物，返回原车道
     *     0xEF=UDLC:非驾驶员操作通用原因，返回原车道
     *     0xF0-0x12C预留
     *     0x12D=ALC:LaneChangeToLeftForPathThroughRamp前方接近匝道，即将向左换道
     *     0x12E=ALC:LaneChangeToRightForPathThroughRamp前方接近匝道，即将向右换道
     *     0x12F=ALC:LaneChangeForQuickRoad,即将汇入主路
     *     0x130=ALC:LaneChangeToLeft即将向左换道
     *     0x131=ALC:LaneChangeToRight即将向右换道
     *     0x132=ALC:LaneChangeToLeftForSurpassTheCar,即将向左超车
     *     0x133=ALC:LaneChangeToRightForSurpassTheCar,即将向右超车
     *     0x134=ALC:向左自动换道-道路更畅通
     *     0x135=ALC:向左自动换道-超越前车
     *     0x136=ALC:向左自动换道-避让前方障碍物
     *     0x137=ALC:向左自动换道-避让前方异常车辆
     *     0x138=ALC:向左自动换道-道路前方有道路施工
     *     0x139=ALC:向左自动换道-提前避让右侧汇入车辆
     *     0x13A=ALC:向左自动换道-避让右侧汇入车辆
     *     0x13B=ALC:向左自动换道-前方道路即将向左合并
     *     0x13C=ALC:向左自动换道-避让右侧大型车辆
     *     0x13D=ALC:向左自动换道-避让后方大型车辆
     *     0x13E=ALC:向右自动换道-道路更畅通
     *     0x13F=ALC:向右自动换道-超越前车
     *     0x140=ALC:向右自动换道-道路前方有障碍物
     *     0x141=ALC:向右自动换道-道路前方有异常车辆
     *     0x142=ALC:向右自动换道-道路前方有道路施工
     *     0x143=ALC:向右自动换道-提前避让左侧汇入车辆
     *     0x144=ALC:向右自动换道-避让左侧汇入车辆
     *     0x145=ALC:向右自动换道-前方道路即将向右合并
     *     0x146=ALC:向右自动换道-避让左侧大型车辆
     *     0x147=ALC:向右自动换道-避让后方大型车辆
     *     0x148=ALC:自动换道已取消（主动）
     *     0x149=ALC:避让侧后方来车，取消自动换道
     *     0x14A=ALC:避让危险车辆，取消自动换道
     *     0x14B=ALC:避让行人，取消自动换道
     *     0x14C=ALC:避让障碍物，取消自动换道
     *     0x14D=ALC:非驾驶员操作通用原因，取消自动换道
     *     0x14E-0x1FF预留
     *     "
     */
    @PropertyDefine(topic = "GW_244/ACC_ADCNotice", type = Integer.class)
    public static final int GW_244_ACC_ADCNOTICE = MGR_ID << MGR_ID_BIT_OFFSET | 0x9c;

    /**
     * 发动机运行状态
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     *     0x0:Stop
     *     0x1:Crank
     *     0x2:Running
     *     0x3:Reserved
     */
    @PropertyDefine(topic = "GW_1E5/EmsEngSts", type = Integer.class)
    public static final int GW_1E5_EMSENGSTS = MGR_ID << MGR_ID_BIT_OFFSET | 0x9d;

    /**
     * 车外温度信号
     * <br/>
     * Attribute: <br/>
     * {access, READ} <br/>
     * {group, VENDOR} <br/>
     * params:
     */
    @PropertyDefine(topic = "GW_1E5/TmsAcEnvtlT", type = Float.class)
    public static final int GW_1E5_TMSACENVTLT = MGR_ID << MGR_ID_BIT_OFFSET | 0x9e;
}
