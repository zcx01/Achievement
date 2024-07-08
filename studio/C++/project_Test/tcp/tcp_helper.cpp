#include "tcp_define.hpp"
#include "tcp_send.hpp"
#include "tcp_helper.hpp"
#include "tcp_data_analy.hpp"
#include "ic_log.h"
#include "zlib.h"
#include "data_store_fetch.hpp"

#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace TD;

void response(uint8_t sid, uint8_t mid, uint16_t errorcode)
{
    uint8_t content[sizeof(errorcode)];
    convertIntToBigEndianArray(errorcode, content, 2);
    std::vector<uint8_t> data(content, content + 2);
    response(TSP_STATUS_ERROR, TSP_TYPE_ERROR, sid, mid, data);
}

void response(uint8_t status, uint16_t type, uint8_t sid, uint8_t mid, const std::vector<uint8_t> &data)
{
    std::vector<TLVConent> TLVContents;
    {
        TLVConent content;
        content.type = TSP_TYPE_STATUS;
        content.valuesLenghtSize = 1;
        content.values.push_back(status);
        TLVContents.push_back(content); // 1
    }

    if (!data.empty())
    {
        TLVConent content;
        content.type = type;
        content.valuesLenghtSize = (status == TSP_STATUS_ERROR ? 1 : 2);
        content.values = data;
        TLVContents.push_back(content);
    }

    MessageData msgData;
    MessageBody body;
    body.sid = sid;
    body.mid = mid;
    TcpDataAnaly::setTLV(TLVContents, body.TLVs);

    AppData appData{msgData, body};
    {
        TcpSend::instance().sendMessage(appData);
        print_app_data("", appData);
    }
}

void parse_tlv(const std::vector<uint8_t> &input, std::map<int, std::vector<uint8_t>> &output)
{
    size_t index = 0;
    while (index + 3 < input.size())
    {
        uint16_t type = (uint16_t)(input[index] << 8) + input[index + 1];
        index += 2;
        uint16_t len = (uint16_t)(input[index] << 8) + input[index + 1];
        index += 2;
        if (input.size() > index + len - 1)
        {
            output[type] = std::vector<uint8_t>(input.begin() + index, input.begin() + index + len);
            index += len;
        }
        else
        {
            output[type] = std::vector<uint8_t>(input.begin() + index, input.end());
            break;
        }
    }
}

std::map<uint32_t, uint32_t> canids;

void parse_tlv(uint8_t *data, int msgLenght)
{
    int uselen = 2;
    uint16_t type = convertBigEndianToInt(data + uselen, 2);
    uselen += 2;
    uint16_t len = convertBigEndianToInt(data + uselen, 2);
    uselen += 2;

    if (type == 61000)
    {
        for (int i = uselen; i < msgLenght;)
        {
            int64_t time_ms = convertBigEndianToInt(data + i, 6);
            i += 6;
            uint16_t can_id = convertBigEndianToInt(data + i, 2);
            i += 2;
            uint8_t len = convertBigEndianToInt(data + i, 1);
            i += 1;

            // if (len % 8 != 0)
            // {
            //     IC_LOG_INFO("send data error sid %d, mid %d, type %d, time %lu, canid 0x%02x, len %d, i %d, total %u", data[0], data[1], type, time_ms, can_id, len, i, msgLenght);
            // }

            i += len;

            IC_LOG_INFO("send data sid %d, mid %d, type %d, time %lu, canid 0x%02x, len %d, size %u", data[0], data[1], type, time_ms, can_id, len, msgLenght - 2);
        }

        uselen += len;
    }
    else
    {
        unsigned long outLen = len + 100;
        uint8_t outcontent[outLen];
        memset(outcontent, 0, outLen);
        int ret = uncompress(outcontent, &outLen, data + uselen, msgLenght - uselen);

        for (size_t i = 0; i < outLen;)
        {
            int64_t time_ms = convertBigEndianToInt(outcontent + i, 6);
            i += 6;
            uint16_t can_id = convertBigEndianToInt(outcontent + i, 2);
            i += 2;
            uint8_t len = convertBigEndianToInt(outcontent + i, 1);
            i += 1;

            // if (len % 8 != 0 || len == 0)
            // {
            //     IC_LOG_INFO("send data error sid %d, mid %d, type %d, time %lu, canid 0x%02x, len %d, i %lu, total %lu", data[0], data[1], type, time_ms, can_id, len, i, outLen);
            // }

            i += len;

            // if ( data[1] == 17)
            // {
            //     if (canids.find(can_id) == canids.end())
            //     {
            //         canids[can_id] = 1;
            //     }
            //     else
            //     {
            //         canids[can_id] += 1;
            //     }
            // }
            

            IC_LOG_INFO("send data sid %d, mid %d, type %d, time %lu, canid 0x%02x, len %d, cnt %d", data[0], data[1], type, time_ms, can_id, len, canids[can_id]);
        }

        uselen += len;
    }
}

void print_app_data(const std::string topic, const TD::AppData &appData)
{
    size_t len = appData.body.TLVs.size();
    char *buff = new char[len * 3 + 1];
    ::memset(buff, 0, len * 3 + 1);
    for (size_t i = 0; i < len; i++)
    {
        sprintf(buff + i * 3, "%02x ", appData.body.TLVs[i]);
    }

    IC_LOG_INFO("topic: %s send to tsp, sid %u, mid %u, len %lu, datas %s", topic.c_str(), appData.body.sid, appData.body.mid, len, buff);

    delete[] buff;
}

std::string getDnsHost()
{
    float value = 0;
    if (DataStoreFetch::instance().getValue("Settings/Env/Set", value, false))
    {
        IC_LOG_INFO("load Settings/Env/Set val %f", value);
    }
    else
    {
        IC_LOG_ERROR("load Settings/Env/Set error, val %f", value);
    }


    if (value == 0)
    {
        return "https://incall.changan.com.cn";
    }

    return "https://pre-incall.changan.com.cn";
}