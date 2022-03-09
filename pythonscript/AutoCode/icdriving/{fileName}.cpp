#include "{fileName}.hpp"
#include "drive_info_common.hpp"

void {ClassName}::state_process(const SignalMsg &sig_msg)
{
    if (fds::judgePowerAndSigTimeOut(&CANSIG_{1}_g,std::bind(&{ClassName}::publishInvalid, this, std::placeholders::_1), {2}))
    {
    }
    else
    {
        union veh_signal_value raw_value;
        if (!GetCommonSigPhysicalValue(raw_value, &CANSIG_{1}_g))
        {
            TB_LOG_ERROR("get siginal value error. return");
            return;
        }

        signalChange(raw_value.val_{4}, {2});
    }
}

void {ClassName}::signalChange(float value,std::string topic)
{
    uint32_t bcmPwrStsFbValue = 0;
    if (1 != GetBcmPwrStsFbValue(bcmPwrStsFbValue))
    {
        TB_LOG_ERROR("GetBcmPwrStsFbValue error. return");
        publishInvalid(topic);
        return;
    }

    publishValue(value,topic);
}

void {ClassName}::publishValue(float value,std::string topic)
{
    TB_LOG_INFO("{ClassName}  %s[%f]",topic.c_str(), value);
    SendDriveInfo(topic, PayloadInfo{value, true});
}

void {ClassName}::publishInvalid(std::string topic)
{
    TB_LOG_INFO("{ClassName} %s Invalid",topic.c_str());
    SendDriveInfo(topic, PayloadInfo{0, false});
}