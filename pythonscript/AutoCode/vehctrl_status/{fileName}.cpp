#include "{fileName}.hpp"
#include <iostream>
#include "structs/payload_info.h"
#include "structs/ipc_message.h"
#include "ipc/megaipc_api.h"
#include "topic/ipc_topic_new_def.h"
#include "fds_common_codes.hpp"

using namespace megaipc;

//{1} {2}
void {ClassName}::addSignalAndTop(struct veh_signal * s, const std::string &t)
{
    subscribe(s);
    signal=s;
    topic = t;
    subscribe((struct veh_signal *)&CANSIG_GW_288__BcmPwrStsFb_g);
}


void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    TB_LOG_INFO("{ClassName}");

    float value = 0;
    veh_signal_value  raw_value;
    signal_status status;

	uint32_t bcmPwrStsFbValue = 0;

    if (1 != fds::GetBcmPwrStsFbValue(bcmPwrStsFbValue))
    {
        TB_LOG_INFO("{ClassName} powerSts: %d", bcmPwrStsFbValue);
        return;
    }
    if(signal == nullptr)
    {
        return;
    }
    if (signal->is_timeout)
    {
        return;
    }

    if(signal->is_timeout)
    {
        publish_status(topic,value,false);
        TB_LOG_ERROR("{1} time out.");
        return;
    }
    
    status = signal->GetValue.fpGetter(&raw_value,nullptr);
    if (status != eSigStatus_Ok)
    {
        TB_LOG_ERROR("{1} signal get error.");
        return;
    }    
    value = raw_value.val_uint32_t;
    
    publish_status(topic,value,true);
}

void {ClassName}::publish_status(const std::string &topic, float value,bool isVaild)
{
    nlohmann::json j = PayloadInfo{ value, isVaild, "", false, ValueType::FLOAT};

    std::string msg = j.dump();
    TB_LOG_INFO("{ClassName} msg: %s %s %f", msg.data(), topic.data(), value);

    //publish message
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    megaipc::MegaIpcApi::instance().publish(topic, message);
}
