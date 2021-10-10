#include "{fileName}.hpp"
#include "structs/payload_info.h"
#include "fds_common_codes.hpp"
#include "topic/ipc_topic_new_def.h"

namespace vehctrl
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	VehCtrlInfo info = fds::ParseAndLogInfo(topic, content);


	fds::CheckPowerAndSendCanFrame(&CANSIG_{1}_g, info.value, signal_value_type::eSigValType_u{4}32_t, topic);
}

}
