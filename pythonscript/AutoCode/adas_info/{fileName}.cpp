#include "{fileName}.hpp"
#include "adas_info_common.hpp"

using namespace fds;
void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    union veh_signal_value raw_value;
    if (!GetCommonSigPhysicalValue(raw_value, &CANSIG_{1}_g))
    {
        TB_LOG_ERROR("get siginal value error. return");
        return;
    }

}

