#include "init_signal_process.hpp"

#include "can_udp_packet_define.h"
#include "signal_transmission.hpp"
#include "parser_can_api.h"
#include "parser_lin_api.h"

void LINData(can_udp_packet_t can_udp_packet)
{
    LIN_PARSER_FrameHandler(can_udp_packet.bus_id, can_udp_packet.can_id, can_udp_packet.message_len, can_udp_packet.data);
}

void CANData(can_udp_packet_t can_udp_packet)
{
    CAN_PARSER_FrameHandler(can_udp_packet.bus_id, can_udp_packet.can_id, can_udp_packet.message_len, can_udp_packet.data);
}

void pData()
{
    can_udp_packet_t can_udp_packet;
    can_udp_packet.bus_id = 1;
    can_udp_packet.can_id = 0x18;
    can_udp_packet.message_len = 8;
    can_udp_packet.data[0] = 0x01;
    can_udp_packet.data[1] = 0x31;
    can_udp_packet.data[2] = 0x40;
    can_udp_packet.data[3] = 0x01;
    can_udp_packet.data[4] = 0x03;
    can_udp_packet.data[5] = 0x64;
    can_udp_packet.data[6] = 0xb3;
    can_udp_packet.data[7] = 0x7d;
    
    LINData(can_udp_packet);

    IC_LOG_DEBUG("%s signal value++++++");
    can_udp_packet.data[3] = 0x05;
    LINData(can_udp_packet);

    
    IC_LOG_DEBUG("%s signal value++++++");
    can_udp_packet.data[3] = 0x05;
    LINData(can_udp_packet);
}


// void meassage_changed_callback(struct veh_message *message, int type)
// {
//     struct veh_signal **pp_signal = (struct veh_signal **)message->signal_array_addr;
//     struct veh_signal *signal;

//     for (; *pp_signal != NULL; pp_signal++)
//     {
//         signal = *pp_signal;
//         IC_LOG_DEBUG("%s signal value----", signal->sig_name);
//         if(fds::SignalTransmission::instance()->signal_changed_callback(signal,true,true))
//         {
//             return;
//         }
//     }
// }

void signal_changed_callback(struct veh_signal *signal, int type)
{
    IC_LOG_DEBUG("%s signal value----", signal->sig_name);
    fds::SignalTransmission::instance()->signal_changed_callback(signal, true, false);
}

void set_can_parser_callbacks()
{
    CAN_SetSigChangeHandler(signal_changed_callback);
}

void set_lin_parser_callbacks()
{
    LIN_SetSigChangeHandler(signal_changed_callback);
    // LIN_SetMsgChangeHandler(meassage_changed_callback);
}

void init_signal_process_up()
{
    IC_LOG_INFO("init_signal_process");
    set_can_parser_callbacks();
    set_lin_parser_callbacks();

    pData();
}
