#include "{fileName}.hpp"
#include "structs/payload_info.h"
#include "fds_common_codes.hpp"
#include "topic/ipc_topic_new_def.h"

namespace vehctrl
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	TB_LOG_INFO("state_process: %s, %s", topic.data(), content.data());
	PayloadInfo info = fds::ParseAndLogPayloadInfo(topic, content);
	float value = info.value.get<float>();

	fds::CheckPowerAndSendCanFrame(&CANSIG_{1}_g, value, signal_value_type::eSigValType_{4}_t, topic);
}

}
