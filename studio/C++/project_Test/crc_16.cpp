#include "crc_16.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "crc16.h"
#include "tcp_define.hpp"
#include "crc8.h"

#define UTILITY_CRC16_INIT_VALUE 0xFFFF
#define UTILITY_CRC16_ISINITENABLE true
#define UTILITY_CRC16_POST_EVENT false

#define UTILITY_CRC8_INIT_VALUE 0xFF
#define UTILITY_CRC8_ISINITENABLE true
// void swapBytes(uint8_t* array, size_t size) {
//     size_t i = 0;
//     size_t j = size - 1;
    
//     while (i < j) {
//         std::swap(array[i], array[j]);
//         i++;
//         j--;
//     }
// }

// void bigEndianToLittleEndian(uint8_t* array) {
//     swapBytes(array, 8);
// }

    static void convertIntToBigEndian(int16_t value, uint8_t *data)
    {
        data[1] = static_cast<uint8_t>(value & 0xFF);
        data[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
    }

Crc16Test::Crc16Test(/* args */) 
{
    std::vector<uint8_t> f0 = {0x40,0x88,0x40,0x44,0x7c,0xff,0x0b,0xf7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x06,0xe8};

    uint16_t crc16 = UTILITY_CRC16_Calculate_x161251(UTILITY_CRC16_INIT_VALUE,f0.data(),f0.size()-2,UTILITY_CRC16_ISINITENABLE,UTILITY_CRC16_POST_EVENT);
    uint8_t crc16_t[sizeof(crc16)];

    convertIntToBigEndian(crc16,crc16_t);
    TD::printHex("Crc16Test",crc16_t,sizeof(crc16));
    TD::printHex("Crc16",f0.data()+f0.size()-2,sizeof(crc16));
    if(TD::compareByteArrayWithUint16(crc16,f0.data()+f0.size()-2))
    {
        IC_LOG_INFO("pass");
    }
}

CUSTOMEGISTER(Crc16,Crc16Test)