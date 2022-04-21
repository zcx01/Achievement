#pragma once
#include <string>

#pragma pack(push,1)

typedef struct packet_header
{
    char version;
    char crc_len;
    short packet_count;
    int length;
    int message_type;
    int crc_value;
    short frag_set;
    short frag_offset;
} PACKET_HEADER;

#pragma pack(pop)