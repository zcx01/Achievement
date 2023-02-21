#pragma once

#include "parser_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif
    extern void CAN_SetMsgChangeHandler(fpMsgChangeHandler_t func);
    extern void CAN_SetSigChangeHandler(fpSigChangeHandler_t func);
    extern void CAN_SetMsgTimeoutHandler(fpMsgTimeoutHandler_t func);
    extern void CAN_MessageElapseTime(int bus_id, int time_ms, int restart);
    extern void CAN_SetSignalChangedHook_GW_1C2__EspVehSpd(fpSignalChangedHook_t hook);

    extern void LIN_SetMsgChangeHandler(fpMsgChangeHandler_t func);

    extern void LIN_SetSigChangeHandler(fpSigChangeHandler_t func);
    extern void LIN_SetMsgTimeoutHandler(fpMsgTimeoutHandler_t func);

    
    
    extern void CAN_PARSER_FrameHandler(uint32_t bus_id, uint32_t frame_id, uint8_t frame_dlc, uint8_t *frame_bytes);

    extern void LIN_PARSER_FrameHandler(uint32_t bus_id, uint32_t frame_id, uint8_t frame_dlc, uint8_t *frame_bytes);

    extern void init_signal_process_up();
    extern void init_signal_process_down();
    extern void qnx_timer_handler();

#ifdef __cplusplus
}
#endif