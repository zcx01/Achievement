#include "tcp_define.hpp"
#include "tcp_send.hpp"
#include "tcp_helper.hpp"
#include "tcp_data_analy.hpp"
#include "ic_log.h"

#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace TD;

void response(uint8_t sid, uint8_t mid, uint16_t errorcode)
{
    uint8_t content[sizeof(errorcode)];
    convertIntToBigEndianArray(errorcode, content, 4);
    std::vector<uint8_t> data(content, content + 4);
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
        content.valuesLenghtSize = 2;
        content.values = data;
        TLVContents.push_back(content);
    }

    MessageData msgData;
    MessageBody body;
    body.sid = sid;
    body.mid = mid;
    TcpDataAnaly::setTLV(TLVContents, body.TLVs);

    AppData appData{msgData, body};
    nlohmann::json value(appData);
    std::ostringstream os;
    os << value.dump() << std::endl;
    string str = os.str();
    {
        IC_LOG_INFO("send to tsp, status %u, type %u, sid %u, mid %u, data %s", status, type, sid, mid, str.c_str());
        TcpSend::instance().sendMessage(appData);
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