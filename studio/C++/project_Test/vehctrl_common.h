#ifndef __VEHCTRL_COMMON__H
#define __VEHCTRL_COMMON__H

#include <string.h>
#include "base_library.h"
#include "crc8.h"

#define DEFAULT_CAN_MSG_FRAME_SIZE (74)
#define DEFAULT_LIN_MSG_FRAME_SIZE (18)

#define DEFAULT_CTRL_DATA_SIZE (8)
#define DEFAULT_CTRL_FRAME_SIZE (13)
#define DEFAULT_CTRL_DATA_FLAG (0x0A)
#define DEFAULT_SIGNAL_DATA_LEN (18)
#define SPI_CTRL_DATA_FLAG (0x11)


#define UARTRPC_SVC_TOPIC_VEH_CTRL_REQ     "uartrpc_svc/veh_ctrl/req"
#define UARTRPC_SVC_TOPIC_VEH_CTRL_RESP    "uartrpc_svc/veh_ctrl/resp"

#define UARTRPC_SVC_IPC_TOPIC_DOWNLINK     "uartrpc/svc/downlink"
#define UARTRPC_SVC_IPC_TOPIC_UPLINK       "uartrpc/svc/uplink"

#define SPIRPC_SVC_TOPIC_VEH_CTRL_REQ       "spirpc_svc/veh_ctrl/req"
#define SPIRPC_SVC_TOPIC_VEH_CTRL_RESP      "spirpc_svc/veh_ctrl/resp"

#ifdef __cplusplus
#include <typeinfo>

enum VehctrlStatusCode
{
    VEHCTRL_STATUS_SUCCESS = 0,
    VEHCTRL_STATUS_CRC_ERROR = 1,
    VEHCTRL_STATUS_FORMAT_ERROR = 2,
    VEHCTRL_STATUS_COUNTER_SAME = 3
};

struct vehctrl_ackmsg
{
    uint8_t proto_id{0};
    uint8_t msg_type{0};
    uint8_t cycle_count{0};
    uint8_t status_code{0};
};


    /*
     * @brief 编码单帧下行控制信号(旧方案value使用float 统配所有类型存在经度转换损失)
     * @param  sig              CAN信号结构体
     * @param  value            信号值
     * @param  value_type       信号值类型
     * @param  out_data         编码后的数据
     */

int codec_vehctrl_data(struct veh_signal *sig, float value, enum signal_value_type value_type, uint8_t *out_data, uint8_t msg_type = 0, uint8_t sig_count = 1, bool spi_flag = false);


uint8_t next_cycle_count(bool spi_flag = false);

int codec_ctrl_frame_head(uint8_t *out_data, uint8_t msg_type = 0, uint8_t sig_count = 1, bool spi_flag = false);

int codec_ctrl_frame_crc(uint8_t *frame_data, uint32_t frame_len);

uint8_t read_cycle_count(const uint8_t *frame_data);


/**
 * @brief 编码单个下行控制信号(新方案实现：使用模板类型T统配所有类型 并校验与parser生成的sig_type是否匹配)
 * @param  sig              CAN信号结构体
 * @param  value            信号值
 * @param  out_data         编码后的数据
 */
template <typename T>
int codec_sigle_down_signal_data(struct veh_signal *sig, T value, uint8_t *out_data)
{
    if (sig == NULL || out_data == NULL)
    {
        IC_LOG_ERROR("Error: %s", "sig or out_data is null");
        return -1;
    }

    struct veh_message *p_msg = (struct veh_message *)sig->p_veh_message;
    if (p_msg == NULL)
    {
        IC_LOG_ERROR("Error:, %s", "p_msg is null");
        return -1;
    }

    int length = DEFAULT_CTRL_DATA_SIZE;
    VehSignalValue_t val;
    memset(val.buffer, 0, 8);
    uint16_t start_bit = (uint16_t)sig->orig_start_bit;

    memcpy(out_data, (char *)&p_msg->msg_id, 2);
    memcpy(out_data + 2, (char *)&start_bit, 2);
    memcpy(out_data + 4, (char *)&length, 1);

    if (typeid(T) == typeid(float) && strcmp(sig->sig_type, "float") == 0)
    {
        val.val_float = value;
    }
    else if (typeid(T) == typeid(int32_t) && strcmp(sig->sig_type, "int32_t") == 0)
    {
        val.val_int32_t = value;
    }
    else if (typeid(T) == typeid(uint32_t) && strcmp(sig->sig_type, "uint32_t") == 0)
    {
        val.val_uint32_t = value;
    }
    else if (typeid(T) == typeid(int64_t) && strcmp(sig->sig_type, "int64_t") == 0)
    {
        val.val_int64_t = value;
    }
    else if (typeid(T) == typeid(uint64_t) && strcmp(sig->sig_type, "uint64_t") == 0)
    {
        val.val_uint64_t = value;
    }
    else
    {
        IC_LOG_ERROR("Error: signal val type error!");
        return -1;
    }
    memcpy(out_data + 5, val.buffer, length);
    return length;
}

int decode_ctrl_ackmsg(const uint8_t *data, uint32_t data_len, struct vehctrl_ackmsg *ackmsg);

#endif

#endif /* __VEHCTRL_COMMON__HPP */
