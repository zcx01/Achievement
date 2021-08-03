#include "{fileName}.hpp"
#include "structs/vehctrl_info.h"
#include "fds_common_codes.hpp"

namespace DriveAssist
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	VehCtrlInfo info = fds::ParseAndLogInfo(topic, content);


	fds::PowerONAndSendCanFrame(&CANSIG_{1}_g, info.value, signal_value_type::eSigValType_u{4}32_t, topic);
}

}
