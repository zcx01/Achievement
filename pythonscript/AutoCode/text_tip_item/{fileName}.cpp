#include "{fileName}.hpp"
#include <iostream>
#include "structs/text_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_new_def.h"
#include "text_tip_common.hpp"


using namespace megaipc;

void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    TB_LOG_INFO("{classname}");

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
        power = raw_value.val_{4}_t;
    }

    status = CANSIG_{1}_g.GetValue.fpGetter( &raw_value,nullptr);
    if (status != eSigStatus_Ok)
    {
        TB_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        result = raw_value.val_{4}_t;
    }

    TB_LOG_INFO("{classname}: %d", result);

    if(CANSIG_GW_288__BcmPwrStsFb_g.is_timeout)
    {
        power=0;
    }

    if(CANSIG_{1}_g.is_timeout)
    {
        result = 0;
    }

    if (power == eCANSIG__GW_288__BcmPwrStsFb_Off_0)
    {
        result = 0;
    }

    fds::addTextInfo({2},result);
}
