
#include "signal_transmission.hpp"
#include "fds_common_codes.hpp"
#include "can_topic.h"
#include <fstream>
namespace fds
{
    SignalTransmission *SignalTransmission::m_instance =new SignalTransmission();

    SignalTransmission* SignalTransmission::instance()
    {
        return m_instance;
    }

    SignalTransmission::SignalTransmission(/* args */)
    {
        getSigNames();
        topic_sigName_down = fds::getTopicSigName();
        sigName_topic_up = fds::getSigNameTopic();

        // nlohmann::json j = PayloadInfo(1);
        // std::string msg = j.dump();
        // if (topicExist("BodyInfo/LowSpeedPedestrianAlarmType/Set"))
        //     SetDownSigName("BodyInfo/LowSpeedPedestrianAlarmType/Set", msg);
        // signal_changed_callback(&CANSIG_CDC_2D2__CdcBioassayWindowReqSts_g, false);
    }

    std::unordered_map<std::string,std::string>  SignalTransmission::getTopicSigName()
    {
        return topic_sigName_down;
    }

    void SignalTransmission::getSigNames()
    {
        struct veh_signal **pp_signal = (struct veh_signal **)(&CAN_ALL_Signal_Array);
        struct veh_signal *signal;
        for (; *pp_signal != NULL; pp_signal++)
        {
            signal = *pp_signal;
            sigName_Ptr[getMessage_SigName(signal)] = signal;
            TB_LOG_INFO("%s", getMessage_SigName(signal));
        }

        pp_signal = (struct veh_signal **)(&LINSIG_ALL_Signal_Array);
        for (; *pp_signal != NULL; pp_signal++)
        {
            signal = *pp_signal;

            sigName_Ptr[getMessage_SigName(signal)] = signal;
            TB_LOG_INFO("%s", getMessage_SigName(signal));
        }
        TB_LOG_INFO("--------------------------------");
    }

    void SignalTransmission::loadConfig(std::string down_config_path,std::string up_config_path)
    {
        try
        {
            nlohmann::json j;
            std::ifstream(down_config_path) >> j;
            for (auto d = j.begin(); d != j.end(); d++)
            {
                topic_sigName_down[d.key()] = d.value();
            }

            std::ifstream(up_config_path) >> j;
            for (auto d = j.begin(); d != j.end(); d++)
            {
                sigName_topic_up[d.key()] = d.value();
            }
        }
        catch (...)
        {
            TB_LOG_INFO("type error");
        }
    }

     std::string SignalTransmission::getMessage_SigName(veh_signal *signal)
    {
        if(signal == nullptr)
        {
            return "";
        }
        std::string message_sig(signal->msg_name,strlen(signal->msg_name));
        message_sig+="/";
        message_sig+=std::string(signal->sig_name,strlen(signal->sig_name));
        return message_sig;
    }

    void SignalTransmission::SetSignalChanged(Sig_Changed_Call func)
    {
        Sig_Changed_Call_Fuc = func;
    }

    void SignalTransmission::signal_changed_callback(veh_signal *signal,bool is_call_fun)
    {
        if (signal == nullptr)
        {
            return;
        }
        if (sigName_Ptr.count(getMessage_SigName(signal)) != 0)
        {
            veh_signal_value physical_value;
            veh_signal_value raw_value;
            signal_status status;
            status = signal->GetValue.fpGetter(&physical_value, &raw_value);
            if (status != eSigStatus_Ok)
            {
                TB_LOG_ERROR("%s signal get error.", signal->sig_name);
                return;
            }
            nlohmann::json value;
            bool isVaild = true;

            if (signal->is_timeout)
            {
                isVaild = false;
            }

            if (NULL != signal->GetIsValueOutOfRange && signal->GetIsValueOutOfRange())
            {
                isVaild = false;
                TB_LOG_DEBUG("status signal value out of range.");
            }
            if (strcmp(signal->sig_type, "float") == 0)
            {
                value = physical_value.val_float;
            }
            else if (strcmp(signal->sig_type, "int32_t") == 0)
            {
                value = physical_value.val_int32_t;
            }
            else if (strcmp(signal->sig_type, "uint32_t") == 0)
            {
                value = physical_value.val_uint32_t;
            }
            else if (strcmp(signal->sig_type, "int64_t") == 0)
            {
                value = physical_value.val_int64_t;
            }
            else if (strcmp(signal->sig_type, "uint64_t") == 0)
            {
                value = physical_value.val_uint64_t;
            }
            else
            {
                TB_LOG_ERROR("%s signal value error.", signal->sig_name);
                return;
            }

            std::map<std::string, uint32_t> raw_value_map;
            raw_value_map["raw_value"] = raw_value.val_uint32_t;
            nlohmann::json j = PayloadInfo{value, isVaild, "", false, raw_value_map};

            std::string msg = j.dump();
            std::string topic;
            std::string sigName = std::string(signal->sig_name,strlen(signal->sig_name));
            if (sigName_topic_up.count(sigName) != 0)
            {
                topic = sigName_topic_up[sigName];
                is_call_fun = true;
            }
            else
            {
                topic = getMessage_SigName(signal);
            }
            TB_LOG_DEBUG("topic:%s content:%s", topic, msg);
            if(is_call_fun)
            {
                if (Sig_Changed_Call_Fuc != nullptr)
                {
                    Sig_Changed_Call_Fuc(topic, msg);
                }
            }
            if(topicExist(topic))
            {
                SetDownSigName(topic,msg);
            }
        }
        else
        {
            TB_LOG_DEBUG("%s no exit", signal->sig_name);
        }
    }

    void SignalTransmission::SetDownSigName(const std::string &topic, const std::string &content)
    {
        std::string sendTopic = topic;
        // if (sendTopic.substr(sendTopic.find_last_of('/') + 1) == "Set")
        // {
        //     sendTopic = sendTopic.substr(0, sendTopic.find_last_of('/'));
        // }

        std::string sigName = sendTopic;
        if (topic_sigName_down.count(sendTopic) != 0)
        {
            sigName = topic_sigName_down[sendTopic];
        }

        if(sigName_Ptr.count(sigName) == 0)
        {
            auto Sig_Ptr = std::find_if(sigName_Ptr.begin(), sigName_Ptr.end(),
                                        [=](const std::unordered_map<std::string, veh_signal *>::value_type item)
                                        {
                                            return item.first.substr(item.first.find_last_of('/')+1) == sigName;
                                        });
            if(Sig_Ptr != sigName_Ptr.end())
            {
                sigName = (*Sig_Ptr).first;
            }
        }
        if(sigName_Ptr.count(sigName) != 0)
        {
            veh_signal *signal = sigName_Ptr[sigName];
            nlohmann::json j = nlohmann::json::parse(content);
            try
            {
                PayloadInfo info = j.get<PayloadInfo>();
                if (strcmp(signal->sig_type, "float") == 0)
                {
                    SendSingleCanValue(signal,info.value.get<float>());
                }
                else if (strcmp(signal->sig_type, "int32_t") == 0)
                {
                    SendSingleCanValue(signal,info.value.get<int32_t>());
                }
                else if (strcmp(signal->sig_type, "uint32_t") == 0)
                {
                    SendSingleCanValue(signal,info.value.get<uint32_t>());
                }
                else if (strcmp(signal->sig_type, "int64_t") == 0)
                {
                    SendSingleCanValue(signal,info.value.get<int64_t>());
                }
                else if (strcmp(signal->sig_type, "uint64_t") == 0)
                {
                    SendSingleCanValue(signal,info.value.get<uint64_t>());
                }
                else
                {
                    TB_LOG_ERROR("%s signal value error.", signal->sig_name);
                    return;
                }
            }
            catch (const std::exception &e)
            {
                TB_LOG_DEBUG("send %s value error", topic);
                return;
            }
        }
        else
        {
            TB_LOG_DEBUG("%s no exit", topic);
        }
    }

    bool SignalTransmission::topicExist(std::string topic)
    {
        return topic_sigName_down.count(topic) !=0;
    }
}


