#include "{fileName}.hpp"
#include "structs/vehctrl_info.h"
#include "fds_common_codes.hpp"

namespace vehctrl
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	VehCtrlInfo info = fds::ParseAndLogInfo(topic, content);


	fds::CheckPowerAndSendCanFrame(&CANSIG_{1}_g, info.value, signal_value_type::eSigValType_u{4}32_t, topic);
}

}
