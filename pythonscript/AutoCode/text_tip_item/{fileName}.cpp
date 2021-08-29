#include "{fileName}.hpp"
#include <iostream>
#include "structs/text_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_def.h"
#include "text_tip_common.hpp"


using namespace megaipc;

void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    TB_LOG_DEBUG("{classname}");

    int power=0;
    int result=0;
    union veh_signal_value raw_value;

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
        result = raw_value.val_uint32_t;
    }

    TB_LOG_DEBUG("{classname}: %d", result);

    if (power == eCANSIG__GW_288__BcmPwrStsFb_Off_0 || sig_msg.is_timeout)
    {
        result = 0;
    }

    nlohmann::json j=TextInfo{result};
    std::string msg = j.dump();
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    MegaIpcApi::instance().publish({2}, message);
}
