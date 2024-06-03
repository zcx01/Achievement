#pragma once

#include <vector>
#include <cstdint>
#include <map>

#include "tcp_define.hpp"

enum TspMsgStatus
{
    TSP_STATUS_OK = 1,
    TSP_STATUS_ERROR = 2,
};

enum TspContentType
{
    TSP_TYPE_STATUS = 4000,
    TSP_TYPE_ERROR = 4004,
    TSP_TYPE_TIMEOUT = 6002,
    TSP_TYPE_REMOTE_DIAGNOSIS = 60000,
    TSP_TYPE_BLUETOOTH_BLACK_LIST_DOWN = 62003,
    TSP_TYPE_BLUETOOTH_BLACK_LIST_UP = 60505,
    TSP_TYPE_SIG_UPLOAD_CLOUD = 61000,
    TSP_TYPE_SIG_UPLOAD_CLOUD_ZIP = 61001
};

enum TspErrorNo
{
    TSP_ERROR_NO_UNKNOWN = 1000,
    TSP_ERROR_NO_RUNNING = 1022,
    TSP_ERROR_NO_TIME_OUT = 1024,
    TSP_ERROR_NO_POWER_NOT_OFF = 1032,
    TSP_ERROR_NO_ENGINE_RUNING = 1032,
    TSP_ERROR_NO_POWER_NOT_ON = 1134,
    TSP_ERROR_NO_CLEAR_CODE_CONDITION = 1135,
    TSP_ERROR_NO_EXECING_DIAGNOSIS = 1136,
    TSP_ERROR_SPEED_NOT_0 = 1194,
};


void response(uint8_t sid, uint8_t mid, uint16_t errorcode);
void response(uint8_t status, uint16_t type, uint8_t sid, uint8_t mid, const std::vector<uint8_t> &data);
void parse_tlv(const std::vector<uint8_t> &input, std::map<int, std::vector<uint8_t>> &output);
void parse_tlv(uint8_t *data, int msgLenght);
void print_app_data(const std::string topic, const TD::AppData& appData);
