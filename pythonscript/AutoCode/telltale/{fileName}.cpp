#include "{fileName}.hpp"
#include <iostream>
#include "structs/telltale_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_def.h"
#include "telltale_common.hpp"

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
        if (signal == eCANSIG__{1}_off_0)
        {
            result = LAMP_OFF;
        }
        else if (signal == eCANSIG__{1}_on_1)
        {
            result = LAMP_ON;
        }
    }
    return result;
}
void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    TB_LOG_DEBUG("{classname}");

    int power=0;
    int leakage=0;
    union veh_signal_value raw_value;
    result_type result;
    signal_status status;

    status = CANSIG_GW_288__BcmPwrStsFb_g.GetValue.fpGetter(nullptr, &raw_value);
    if (status != eSigStatus_Ok)
    {
        TB_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        power = raw_value.val_uint32_t;
    }

    status = CANSIG_{1}_g.GetValue.fpGetter(nullptr, &raw_value);
    if (status != eSigStatus_Ok)
    {
        TB_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        leakage = raw_value.val_uint32_t;
    }

    
    result=normal_logic(power,leakage);
    fds::TimeOutHandle(&result,&CANSIG_{1}_g,(int)LAMP_OFF);

    TB_LOG_DEBUG("{classname}: %d", result);

    nlohmann::json j;

    switch (result)
    {
    case LAMP_OFF:
        j = TelltaleInfo{LampState::TELLTALE_OFF};
        break;
    case LAMP_ON:
        j = TelltaleInfo{LampState::TELLTALE_ON};
    case LAMP_FLASH:
        j = TelltaleInfo{LampState::TELLTALE_ON, LampColor::DEFAULT, 1000, 0.5};
        break;
    }

    std::string msg = j.dump();
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    MegaIpcApi::instance().publish({2}, message);
}
