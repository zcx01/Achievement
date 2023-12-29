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

#define TCPCONNECTSTATUS "TcpConnectStatus"
#define TCPSENDSTATUS "TcpSendStatus"

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

    enum TcpConnectStatus
    {
        NoConnect,
        Connecting,
        ConnectFail,
        ConnectSuccess,
        DisConnect
    };

    enum TcpSendStatus
    {
        Sending,
        SendFail,
        SendFinish
    };


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

        bool isVaild()
        {
            return up_down != 0;
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
    } MessageBody;

    typedef struct app_data
    {
        MessageData data;
        MessageBody body;
        app_data(const MessageData &d, const MessageBody &b)
        {
            data = d;
            body = b;
        }
    }AppData;
 
    typedef struct a35_send_reply
    {
        uint8_t flag ;                  // AG35与8155相关状态同步为0x03
        uint8_t noticeFlag;             // AG35通知8155报文发送结果状态
        uint8_t sid;                    // sid
        uint8_t mid;                    // mid
        uint8_t requestId[6];           // 年月日,第6位为流水号 8bit 为偶数，前2个bit定义为0x01，剩下的bit循环计数
        uint8_t status = 0;             // 报文发送结果状态0:发送成功1:发送失败
        a35_send_reply()
        {
            memset(this,0,sizeof(a35_send_reply));
            flag = 0x3;
            noticeFlag = 0x1;
        }
    }A35SendReply;
    
#pragma pack(pop)

} // TD

