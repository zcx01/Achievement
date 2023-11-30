#pragma once
#include <string>
#include "mcu_crc_calculate.h"
#include <cstring>
#include <vector>
#include <functional>
#include "ic_log.h"
#include <random>

#define  BITSIZE 8  
#define  HEADERFLAG 0x5a    //头标识
#define  CRCLENGHT  2       //crc长度

#define CRC16_INIT_VALUE 0
#define CRC16_ISINITENABLE true
#define MAX_LENGHT 2048
#define TCP_IP "172.16.2.29"
#define TCP_PORT 50001

using RecDataFun = std::function<void (uint8_t *, int)>;

namespace TD
{
    static void convertIntToLittleEndian(int16_t value, uint8_t *data)
    {
        data[0] = static_cast<uint8_t>(value & 0xFF);
        data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    }

    static int16_t convertLittleEndianToInt(const uint8_t *data)
    {
        int16_t result = static_cast<int16_t>(data[0]) | (static_cast<int16_t>(data[1]) << 8);
        return result;
    }

    // static void convertInt16ToBigEndianArray(int16_t value, uint8_t *array)
    // {
    //     array[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
    //     array[1] = static_cast<uint8_t>(value & 0xFF);
    // }

    static uint64_t convertBigEndianToInt(const uint8_t *bytes, uint32_t lenght)
    {
        uint64_t value = 0;
        for (uint32_t i = 0; i < lenght; i++)
        {
            value = (value << 8) | bytes[i];
        }
        return value;
    }

    static void convertIntToBigEndianArray(int value, uint8_t *array, uint32_t size)
    {
        for (uint32_t i = 0; i <  size; i++)
        {
            array[i] = static_cast<uint8_t>((value >> (8 * (size - 1 - i))) & 0xFF);
        }
    }

    static bool compareByteArrayWithUint16(const uint16_t &value, const uint8_t *byteArray)
    {
        uint8_t valueArray[2];
        memcpy(valueArray, &value, sizeof(uint16_t));
        return memcmp(byteArray, valueArray, sizeof(uint16_t)) == 0;
    }

    static bool checkCrc(uint8_t *crc, uint8_t *app_data, uint32_t app_data_lenght)
    {
        auto crc16 = crc16_calculate(CRC16_INIT_VALUE, app_data, app_data_lenght, CRC16_ISINITENABLE);
        return compareByteArrayWithUint16(crc16, crc);
    }

    static void crcCalculate(uint8_t *crc, uint8_t *app_data, uint32_t app_data_lenght)
    {
        auto crc16 = crc16_calculate(CRC16_INIT_VALUE, app_data, app_data_lenght, CRC16_ISINITENABLE);
        convertIntToLittleEndian(crc16, crc);
    }

    static void printHex(const std::string &topic, uint8_t *data, uint8_t len)
    {
        char buff[512] = {0};
        for (int i = 0; i < len; i++)
        {
            sprintf(buff + i * 3, "%02x ", data[i]);
        }
        IC_LOG_INFO("topic: %s %s\n", topic.c_str(), buff);
    }

    static void printVectorHex(std::string topic, const std::vector<uint8_t> &values)
    {
        if (values.empty())
        {
            IC_LOG_DEBUG("values is empty");
            return;
        }
        const int &size = values.size();
        uint8_t *data = const_cast<uint8_t *>(values.data());
        printHex(topic, data, size);
    }

    static void Random16(uint8_t *random,int lenght)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint16_t> dis(0, 0xffff);
        convertIntToBigEndianArray(dis(gen), random,lenght);
    }

#pragma pack(push, 1)
    typedef struct tcp_packet_header
    {
        uint8_t flag;
        uint8_t ack;
        uint8_t control;
        uint8_t channel;
        uint8_t reserved[4];
        uint8_t counter[2];
        uint8_t length[2];
        tcp_packet_header()
        {
            memset(this,0,sizeof(tcp_packet_header));
        }

    } TCP_PACKET_HEADER;

    typedef struct message_data
    {
        uint8_t flag = 0;             // 固定值，表示是和云端通信
        uint8_t up_down;              // 0x1 上行(回复云端或者指令执行结果) 0x2 下行(云端下发的指令或者云端回复)
        uint8_t statusCode;           // 描述请求或响应的状态（错误）码
        uint8_t ackFlag;              // 0：代表响应消息，接收方接收到消息后，不需要对该消息进行回复 1：代表请求消息，接收方接收到消息后，需要回复确认接收消息，如回复 CmdReceivedMsg
        uint8_t requestId[6];         // 年月日,第6位为流水号 8bit 为偶数，前2个bit定义为0x01，剩下的bit循环计数
        uint8_t encryptFlag = 0;      // 加密标识 0：表示明文，未加密或已解密 1：表示使用128bitAES对MessageBody明文内容进行加密；
        uint8_t messageBodyLenght[2]; // MessageBody消息体的长度
        message_data()
        {
            memset(this,0,sizeof(message_data));
        }
    } MessageData;

    struct TLVConent
    {
        uint16_t type = 0;
        uint8_t valuesLenghtSize = 1; // values长度大小的字节
        std::vector<uint8_t> values;
    };

    typedef struct message_body
    {
        uint8_t Random[2];
        uint8_t sid;
        uint8_t mid;
        std::vector<uint8_t> TLVs; // type参数键的ID、lenght长度、value值三者组成的集合

        message_body()
        {
            Random16(Random,sizeof(Random));
            memset(&sid,0,sizeof(sid));
            memset(&mid,0,sizeof(mid));
        }
        
        int getRSMlenght() const
        {
            return sizeof(Random)+sizeof(sid)+sizeof(mid);
        }


        std::vector<TLVConent> getTLV(uint8_t fixedlenghtSize,std::vector<uint8_t> lenghtSizes={})
        {
            std::vector<TLVConent> TLVContents;
            int TLVLenghtInt = TLVs.size();
 
            int uselenght = 0;
            auto TLVData = TLVs.data();
            uint8_t lenghtSize = fixedlenghtSize;
            while (uselenght < TLVLenghtInt)
            {
                TLVConent content;
                content.type = convertBigEndianToInt(TLVData + uselenght,sizeof(content.type));
                uselenght += sizeof(content.type);

                if (lenghtSize == 0 && lenghtSizes.size() > TLVContents.size())
                {
                    lenghtSize = lenghtSizes[TLVContents.size()];
                }
                uint8_t lenght[lenghtSize];
                memcpy(lenght, TLVData + uselenght, sizeof(lenght));
                uselenght += sizeof(lenght);

                auto intLenght = convertBigEndianToInt(lenght, sizeof(lenght));
                for (uint64_t i = 0; i < intLenght; ++i)
                {
                    uint8_t value;
                    memcpy(&value, TLVData + uselenght, sizeof(value));
                    uselenght += sizeof(value);
                    content.values.push_back(value);
                }
                TLVContents.push_back(content);
            }
            return TLVContents;
        }

        void setTLV(const std::vector<TLVConent> &TLVContents)
        {
            int TLVslenght = 0;
            int uselenght = 0;
            for (auto content : TLVContents)
            {
                TLVslenght += sizeof(content.type) + content.valuesLenghtSize + content.values.size();
            }
            uint8_t TLVDatas[TLVslenght];
            memset(TLVDatas,0,sizeof(TLVDatas));

            for (auto content : TLVContents)
            {
                convertIntToBigEndianArray(content.type, TLVDatas + uselenght,  sizeof(content.type));
                uselenght += sizeof(content.type);

                uint8_t lenght[content.valuesLenghtSize];
                convertIntToBigEndianArray(content.values.size(), lenght, sizeof(lenght));
                memcpy(TLVDatas + uselenght, lenght, sizeof(lenght));
                uselenght += sizeof(lenght);

                memcpy(TLVDatas + uselenght, content.values.data(), content.values.size());
                uselenght += content.values.size();
            }
            printHex("TLVDatas",TLVDatas,TLVslenght);
            TLVs = std::vector<uint8_t>(TLVDatas,TLVDatas+TLVslenght);
        }

    } MessageBody;

    static uint64_t getMessageId(const MessageData &msgData,const MessageBody &msgBody)
    {
        uint64_t value = convertBigEndianToInt(msgData.requestId, sizeof(msgData.requestId)); // 占6位
        value |= msgBody.mid << 6;
        value |= msgBody.sid << 7;
        return value;
    }

#pragma pack(pop)

} // TD

