#include 
#include <iostream>
#include "structs/telltale_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_def.h"

using namespace megaipc;

{ClassName}::result_type {ClassName}::normal_logic(int power, int signal)
{
    result_type result;

    if (power == eCANSIG__GW_288__BcmPwrStsFb_Off_0)
    {
        result = LAMP_OFF;
    }
    else
    {
        if (signal == eCANSIG__GW_1F7__FccuH2EmgyLamp_No_error_0)
        {
            result = LAMP_OFF;
        }
        else if (signal == eCANSIG__GW_1F7__FccuH2EmgyLamp_Yellow_light_on_1)
        {
            result = LAMP_YELLOW;
        }
        else if (signal == eCANSIG__GW_1F7__FccuH2EmgyLamp_Red_light_on_2)
        {
            result = LAMP_YELLOW;
        }
    }
    return result;
}
void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    IC_LOG_INFO("{classname}");

    int power;
    int leakage;
    union veh_signal_value raw_value;
    result_type result;
    signal_status status;

    status = CANSIG_GW_288__BcmPwrStsFb_g.GetValue.fpGetter(nullptr, &raw_value);
    if (status != eSigStatus_Ok)
    {
        IC_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        power = raw_value.val_uint32_t;
    }

    status = CANSIG_GW_1F7__FccuH2EmgyLamp_g.GetValue.fpGetter(nullptr, &raw_value);
    if (status != eSigStatus_Ok)
    {
        IC_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        leakage = raw_value.val_uint32_t;
    }

    
    result=normal_logic(power,leakage);

    if(CANSIG_GW_1F7__FccuH2EmgyLamp_g.is_timeout){
        if(power == 1 || power == 2 || power == 3){
            result = LAMP_RED;
        }
        else{
            result =LAMP_OFF;
        }
    }

    IC_LOG_INFO("{classname}: %d", result);

    nlohmann::json j;

    switch (result)
    {
    case LAMP_OFF:

        j = TelltaleInfo{LampState::TELLTALE_OFF};
        break;
    case LAMP_YELLOW:
        j = TelltaleInfo{LampState::TELLTALE_ON,LampColor::YELLOW};
        break;
    }

    std::string msg = j.dump();
    IpcMessage message = {"", (uint32_t)msg.length(), (uint8_t *)msg.data(), 0, true};
    MegaIpcApi::instance().publish(TOPIC_ICTELLTALE_AUTO_HOLD, message);
}
