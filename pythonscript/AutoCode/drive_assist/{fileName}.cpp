#include "{fileName}.hpp"
#include "structs/vehctrl_info.h"
#include "fds_common_codes.hpp"

namespace DriveAssist
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	IC_LOG_INFO("state_process: %s, %s", topic.data(), content.data());
	PayloadInfo info = fds::ParseAndLogPayloadInfo(topic, content);
	float value = info.value.get<float>();

	fds::SendCanFrame(&CANSIG_{1}_g, value, signal_value_type::eSigValType_{4});
}

}
