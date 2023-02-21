#pragma once
#include "ic_log.h"

/*! Udp数据包最小长度 */
#define MAX_DATA_LEN 200

typedef struct can_udp_packet
{
    uint8_t bus_id;
    uint32_t can_id;
    uint8_t message_len;
    uint8_t data[MAX_DATA_LEN];
    void clone(can_udp_packet *d)
    {
        if(d == nullptr)
        {
            return;
        }
        d->bus_id = this->bus_id;
        d->can_id = this->can_id;
        d->message_len = this->message_len;
        memcpy(d->data, this->data, d->message_len);
    }
} __attribute__((packed)) can_udp_packet_t;