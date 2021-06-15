#include "{fileName}.hpp"
#include <iostream>
#include "structs/vehctrl_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_def.h"
#include "vehctrl_status_common.hpp"
#include "fds_common_codes.hpp"

using namespace megaipc;


void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    TB_LOG_INFO("{classname}");

    int value;
    veh_signal_value  raw_value;
    signal_status status;

	uint32_t bcmPwrStsFbValue = 0;

    if (1 != fds::GetBcmPwrStsFbValue(bcmPwrStsFbValue))
    { 
        TB_LOG_INFO("{classname}   powerSts: %d", bcmPwrStsFbValue);
        return;
    }
	
    status = {0}.GetValue.fpGetter(nullptr, &raw_value);
    if (status != eSigStatus_Ok)
    {
        TB_LOG_ERROR("signal get error.");
        return;
    }
    else
    {
        value = raw_value.val_uint32_t;
    }

    publish_status({1}, value);
}
