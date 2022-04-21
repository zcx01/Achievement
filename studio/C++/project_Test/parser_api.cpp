#include "parser_api.h"
#include <string>

void loadConfig(char* down_config_path,int down_config_path_lenght, char* up_config_path,int up_config_lenght)
{
    fds::SignalTransmission::instance()->loadConfig(std::string(down_config_path,down_config_path_lenght),
    std::string(up_config_path,up_config_lenght));
}
void signal_changed_callback(veh_signal *signal, bool is_call_fun)
{
    fds::SignalTransmission::instance()->signal_changed_callback(signal,is_call_fun);
}
void SetDownSigName(char *topic,int topic_lenght,char *content,int content_lenght)
{
    fds::SignalTransmission::instance()->SetDownSigName(std::string(topic,topic_lenght),std::string(content,content_lenght));
}
void SetSignalChanged(Sig_Changed_Call func)
{
    fds::SignalTransmission::instance()->SetSignalChanged(func);
}
void SetTopicChanged(Topic_Changed_Call func)
{
    fds::SignalTransmission::instance()->SetTopicChanged(func);
}

void SetDownBack(Down_Call func)
{
    fds::SignalTransmission::instance()->SetDownBack(func);
}
