#include "{fileName}.hpp"
#include "structs/payload_info.h"
#include "fds_common_codes.hpp"
#include "topic/ipc_topic_new_def.h"

namespace vehctrl
{

void {ClassName}::state_process(const std::string &topic, const std::string &content)
{
	PayloadInfo info = fds::ParseAndLogPayloadInfo(topic, content);
	float value = info.value.get<float>();
	TB_LOG_INFO("state_process: %s, %s", topic.data(), content.data());

	fds::CheckPowerAndSendCanFrame(&CANSIG_{1}_g, info.value, signal_value_type::eSigValType_{4}_t, topic);
}

}
