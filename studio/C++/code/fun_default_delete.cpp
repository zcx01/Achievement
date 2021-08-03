#include "fun_default_delete.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>

class Magic
{
public:
    Magic() = default;  //显示声明使用编译器生成的构造
    Magic& operator =(const Magic&) = delete;
    Magic(int magic_number);
};

union cansig_vcu_309__vcuvehavrgegycnsein10km_data_t
{
    uint32_t val;
    struct
    {
        uint32_t VcuVehAvrgEgyCnseIn10km__S1 : 3;
        uint32_t VcuVehAvrgEgyCnseIn10km__S0 : 6;
    } fields;
};

union canmsg_vcu_309_data_t
{
    uint8_t buffer[64];
    struct
    {
        uint64_t PAD0;
        uint64_t PAD1 : 55;
        uint64_t VcuFulResiMilgWLTC__S1 : 9;
        uint64_t VcuFulResiMilgWLTC__S0 : 1;
        uint64_t VcuFulResiMilgNEDC : 10;
        uint64_t VcuElecResiMilgWLTC : 10;
        uint64_t VcuElecResiMilgNEDC : 10;
        uint64_t VcuVehEgyCnseSelectCfm : 1;
        uint64_t VcuPwrSplyRst : 1;
        uint64_t VcuEvDrvResiMilg : 13;
        uint64_t VcuVehAvrEgyCnsegInAftPwrSply : 9;
        uint64_t VcuVehAvrEgyCnsegInDrvgCyc : 9;
        uint64_t PAD2 : 24;
        uint64_t VcuVehEgyCnseInTripA : 24;
        uint64_t VcuVehEgyCnseLongTime__S1 : 16;
        uint64_t VcuVehEgyCnseLongTime__S0 : 8;
        uint64_t VcuUnreleasedMilgInLowT : 8;
        uint64_t PAD3 : 3;
        uint64_t VcuVehIncrMilg : 11;
        uint64_t VcuVehChrgSpeedInMilg : 12;
        uint64_t VcuVehResiMilgIn50km : 11;
        uint64_t VcuVehResiMilgIn25km : 11;
        uint64_t PAD4 : 1;
        uint64_t VcuVehResiMilgIn10km : 11;
        uint64_t VcuVehAvrgResiMilgIn50km : 11;
        uint64_t VcuVehAvrgResiMilgIn25km : 11;
        uint64_t VcuVehAvrgResiMilgIn10km : 11;
        uint64_t PAD5 : 10;
        uint64_t VcuVehAvrgEgyCnseInTripA : 9;
        uint64_t PAD6 : 7;
        uint64_t VcuVehAvrgEgyCnse : 9;
        uint64_t VcuVehEgyCnseIn50km : 9;
        uint64_t VcuVehEgyCnseIn25km : 9;
        uint64_t VcuVehEgyCnseIn10km : 9;
        uint64_t VcuVehAvrEgyCnsegIn50km : 9;
        uint64_t VcuVehAvrgEgyCnseIn25km : 9;
        uint64_t VcuVehAvrgEgyCnseIn10km__S1 : 3;
        uint64_t VcuVehAvrgEgyCnseIn10km__S0 : 6;
        uint64_t VcuVehChrgRest : 1;
        uint64_t VcuVehChrgEgyCnse : 10;
        uint64_t PAD7 : 19;
        uint64_t VcuVehAvrgEgyCnseLongTime : 9;
        uint64_t VcuVehEgyCnseDrivingCyc : 10;
    } signals;
};


void BinaryRecursion(uint16_t n)
{
	int a;
	a = n % 2; // 取余
	n = n >> 1;  //右移一位 相当于除以2
	if(0 != n)
	{
		BinaryRecursion(n);
	}
	std::cout<<a<<std::endl;
}

FunDefaultDeleteTest::FunDefaultDeleteTest(/* args */) 
{
    // union cansig_vcu_309__vcuvehavrgegycnsein10km_data_t SignalData;
    // SignalData.val = 0x1;
    // union canmsg_vcu_309_data_t CANMSG_VCU_309_s;
    // CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S1 = SignalData.fields.VcuVehAvrgEgyCnseIn10km__S1;
    // CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S0 = SignalData.fields.VcuVehAvrgEgyCnseIn10km__S0;
    // BinaryRecursion(CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S1);
    // COUT("----------------")

    int value=0x1ff;
    union canmsg_vcu_309_data_t CANMSG_VCU_309_s;
    CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S1 = value;
    CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S0 = value>>3;
    BinaryRecursion(value>>3);
    COUT("----------------")
    BinaryRecursion(CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S1);
    COUT("----------------")
    BinaryRecursion(CANMSG_VCU_309_s.signals.VcuVehAvrgEgyCnseIn10km__S0);
}

CUSTOMEGISTER(FunDefaultDelete,FunDefaultDeleteTest)