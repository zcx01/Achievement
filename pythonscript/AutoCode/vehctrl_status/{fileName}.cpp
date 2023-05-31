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
    //  subscribe((struct veh_signal *)&CANSIG_GW_288__BcmPwrStsFb_g);
}


void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    IC_LOG_INFO("{ClassName}");

    float value = 0;
    veh_signal_value  raw_value;
    signal_status status;

	//  uint32_t bcmPwrStsFbValue = 0;

    // if (1 != fds::GetBcmPwrStsFbValue(bcmPwrStsFbValue))
    // {
    //     IC_LOG_INFO("{ClassName} powerSts: %d", bcmPwrStsFbValue);
    //     return;
    // }
    if(signal == nullptr)
    {
        return;
    }

    if(signal->is_timeout)
    {
        publish_status(topic,value,false);
        IC_LOG_ERROR("%s time out.",signal->sig_name);
        return;
    }

    if(NULL != signal->GetIsValueOutOfRange && signal->GetIsValueOutOfRange())
    {
        publish_status(topic,value,false);
        IC_LOG_ERROR("status signal value out of range.");
        return;
    }
    
    status = signal->GetValue.fpGetter(&raw_value,nullptr);
    if (status != eSigStatus_Ok)
    {
        IC_LOG_ERROR("%s signal get error.",signal->sig_name);
        return;
    }    
    value = raw_value.val_{4};
    
    publish_status(topic,value,true);
}

void {ClassName}::publish_status(const std::string &topic, float value,bool isVaild)
{
    nlohmann::json j = PayloadInfo{ value, isVaild, "", false};

    std::string msg = j.dump();
    IC_LOG_INFO("{ClassName} msg: %s %s %f", msg.data(), topic.data(), value);

    //publish message
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    megaipc::MegaIpcApi::instance().publish(topic, message);
}
