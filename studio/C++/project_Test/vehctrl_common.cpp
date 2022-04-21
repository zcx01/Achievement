#include "base_library.h"
#include "vehctrl_common.h"

void write_int32(int32_t value, int8_t *out_data)
{
    if (out_data == NULL)
        return;
}

void write_float(float value, int8_t *out_data)
{
    if (out_data == NULL)
        return;
}

int codec_vehctrl_data(struct veh_signal *sig, float value, enum signal_value_type value_type, uint8_t *out_data, uint8_t msg_type, uint8_t sig_count, bool spi_flag)
{
    if (sig == NULL || out_data == NULL)
    {
        TB_LOG_ERROR("Error: %s", "sig or out_data is null");
        return -1;
    }

    if (sig_count == 0)
        sig_count = 1;

    struct veh_message *p_msg = (struct veh_message *)sig->p_veh_message;
    if (p_msg == NULL)
    {
        TB_LOG_ERROR("Error:, %s", "p_msg is null");
        return -1;
    }

    memset(out_data, 0, DEFAULT_CTRL_FRAME_SIZE + 5);

    int length = DEFAULT_CTRL_DATA_SIZE;
    VehSignalValue_t val;
    memset(val.buffer, 0, 8);
    uint16_t start_bit = (uint16_t)sig->orig_start_bit;
    uint8_t cycle_count = next_cycle_count(spi_flag);

    out_data[0] = spi_flag ? SPI_CTRL_DATA_FLAG : DEFAULT_CTRL_DATA_FLAG;
    memcpy(out_data + 1, (char *)&msg_type, 1);
    memcpy(out_data + 2, (char *)&cycle_count, 1);
    memcpy(out_data + 3, (char *)&sig_count, 1);
    memcpy(out_data + 4, (char *)&p_msg->msg_id, 2);
    memcpy(out_data + 6, (char *)&start_bit, 2);
    memcpy(out_data + 8, (char *)&length, 1);
    switch (value_type)
    {
    case eSigValType_float:
        val.val_float = value;
        break;
    case eSigValType_int32_t:
        val.val_int32_t = value;
        break;
    case eSigValType_uint32_t:
        val.val_uint32_t = value;
        break;
    case eSigValType_int64_t:
        val.val_int64_t = value;
        break;
    case eSigValType_uint64_t:
        val.val_uint64_t = value;
        break;
    default:
        TB_LOG_WARNING("value type is unknown");
        break;
    }
    memcpy(out_data + 9, val.buffer, length);

    return length;
}

uint8_t next_cycle_count(bool spi_flag)
{
    static int uart_cycle_count = 1;
    static int spi_cycle_count = 1;
    uint8_t cycle_count = 0;

    if (spi_flag)
    {
        cycle_count = static_cast<uint8_t>(spi_cycle_count++);
        if (spi_cycle_count > 255)
        {
            spi_cycle_count = 1;
        }
    }
    else
    {
        cycle_count = static_cast<uint8_t>(uart_cycle_count++);
        if (uart_cycle_count > 255)
        {
            uart_cycle_count = 1;
        }
    }

    return cycle_count;
}

int codec_ctrl_frame_head(uint8_t *out_data, uint8_t msg_type, uint8_t sig_count, bool spi_flag)
{
    if (!out_data)
    {
        return -1;
    }

    out_data[0] = spi_flag ? SPI_CTRL_DATA_FLAG : DEFAULT_CTRL_DATA_FLAG;
    out_data[1] = msg_type;
    out_data[2] = next_cycle_count(spi_flag);
    out_data[3] = sig_count;
    return 0;
}


int codec_ctrl_frame_crc(uint8_t *frame_data, uint32_t frame_len)
{
    if (!frame_data)
    {
        return -1;
    }
    uint8_t crc = UTILITY_CRC8_Calculate(0, frame_data + 1, frame_len - 2, false);
    frame_data += (frame_len - 1);
    *frame_data = crc;
    return 0;
}

uint8_t read_cycle_count(const uint8_t *frame_data)
{
    if (!frame_data)
    {
        return 0;
    }
    return frame_data[2];
}


int decode_ctrl_ackmsg(const uint8_t *data, uint32_t data_len, struct vehctrl_ackmsg *ackmsg)
{
    if (!data || !ackmsg || data_len < 4)
    {
        return -1;
    }
    ackmsg->proto_id = data[0];
    ackmsg->msg_type = data[1];
    ackmsg->cycle_count = data[2];
    ackmsg->status_code = data[3];
    return 0;
}
