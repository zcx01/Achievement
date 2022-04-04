#pragma once
#include <string>
#include <unordered_map>
typedef struct veh_signal Veh_Signal_t;
typedef void (*Sig_Changed_Call)(std::string,std::string);
namespace fds
{
    class SignalTransmission
    {
    public:
        static SignalTransmission* instance();

        void loadConfig(std::string down_config_path,std::string up_config_path);

        void signal_changed_callback(veh_signal *signal,bool is_call_fun);

        void SetSignalChanged(Sig_Changed_Call func); 

        void SetDownSigName(const std::string &topic,const std::string &content);

        std::unordered_map<std::string,std::string>  getTopicSigName();

        bool topicExist(std::string topic); 

    private:
        SignalTransmission(/* args */);

        void getSigNames(); 

        std::string getMessage_SigName(veh_signal *signal);

        std::unordered_map<std::string, veh_signal *> sigName_Ptr;
        std::unordered_map<std::string/*topic*/,std::string/*sigName*/> topic_sigName_down;
        std::unordered_map<std::string/*sigName*/,std::string/*topic*/> sigName_topic_up;
        Sig_Changed_Call   Sig_Changed_Call_Fuc=nullptr;

        static SignalTransmission* m_instance;
    };
} // fds
