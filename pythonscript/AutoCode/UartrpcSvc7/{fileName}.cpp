#include "{fileName}.hpp"
#include "uartrpc_common.hpp"
#include "fds_common_codes.hpp"

namespace UARTPC
{
    void {ClassName}::state_process(const std::string &topic, const std::string &content)
    {
        IC_LOG_INFO("state_process: %s, %s", topic.data(), content.data());
        PayloadInfo info = fds::ParseAndLogPayloadInfo(topic, content);
    }

    void {ClassName}::deal_process(const std::string &topic, const IpcMessage &msg)
    {
        if(topic == UARTRPC_SVC_IPC_TOPIC_UPLINK)
        {
            PayloadInfo info;
            publish_payloadInfo({2},info);
        }
    }
}