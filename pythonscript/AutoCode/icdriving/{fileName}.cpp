#include "{fileName}.hpp"
#include "drive_info_common.hpp"

void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    if (sig_msg.is_timeout)
    {
        if (sig_msg.signal_addr == &CANSIG_GW_288__BcmPwrStsFb_g)
        {
            TB_LOG_INFO("CANSIG_GW_288__BcmPwrStsFb_g Timeout");
        }
        
        else if (sig_msg.signal_addr == &CANSIG_{1}_g)
        {
            TB_LOG_INFO("{ClassName} {2} Timeout");
        }
        publishInvalid({2});
    }
    else
    {
        union veh_signal_value raw_value;
        if (!GetCommonSigValue(raw_value, sig_msg.signal_addr))
        {
            TB_LOG_ERROR("get siginal value error. return");
            return;
        }

        if (sig_msg.signal_addr == &CANSIG_{1}_g)
        {
            TB_LOG_INFO("{1} Value %u", raw_value.val_uint32_t);
            signalChange(raw_value.val_uint32_t,{2});
        }
    }
}

void {ClassName}::signalChange(float value,std::string topic)
{
    uint32_t bcmPwrStsFbValue = 0;
    if (1 != GetBcmPwrStsFbValue(bcmPwrStsFbValue))
    {
        TB_LOG_ERROR("GetBcmPwrStsFbValue error. return");
        return;
    }

    publishValue(value,topic);
}

void {ClassName}::publishValue(float value,std::string topic)
{
    TB_LOG_INFO("{ClassName} %s[%d]",topic, value);
    bool isValid = true;
    nlohmann::json jsValue;
    jsValue = megaipc::DrivingInfo{(float)value, 0, isValid};
    std::string msg = jsValue.dump();
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    megaipc::MegaIpcApi::instance().publish(topic, message);      //TDB
}

void {ClassName}::publishInvalid(std::string topic)
{
    TB_LOG_INFO("{ClassName} %s 无效",topic);
    bool isValid = false;
    nlohmann::json jsValue;
    jsValue = megaipc::DrivingInfo{(float)0, 0, isValid};
    std::string msg = jsValue.dump();
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    megaipc::MegaIpcApi::instance().publish(topic, message);      //TDB
}