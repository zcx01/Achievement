
#pragma once
#include "signal_transmission.hpp"

extern void loadConfig(char* down_config_path,int down_config_path_lenght, char* up_config_path,int up_config_lenght);

extern void signal_changed_callback(veh_signal *signal, bool is_call_fun);

extern void SetDownSigName(char *topic,int topic_lenght,char *content,int content_lenght);

extern void SetSignalChanged(Sig_Changed_Call func);

extern void SetTopicChanged(Topic_Changed_Call func);

extern void SetDownBack(Down_Call func);
