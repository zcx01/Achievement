#include "test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include "fds_cpp_timer.hpp"
struct PayloadInfo
{
    nlohmann::json value;     /*! 数值 */
    bool valid;               /*! 是否有效 */
    bool relative;            /*! false: 绝对值 true: 相对值 */
    long long time;           /*! unix 时间戳 精度ms */
    nlohmann::json extension; /*! 扩展数据 */

    PayloadInfo(nlohmann::json _value = 0,
                bool _valid = true,
                bool _relative = false,
                long long _time = 0,
                nlohmann::json _extension = nullptr)
    {
        value = _value;
        valid = _valid;
        relative = _relative;
        time = _time;
        extension = _extension;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PayloadInfo, value, valid, relative, time, extension);
};

void publish_uartpc(const std::vector<int>& values)
{
    if (values.empty())
    {
        IC_LOG_INFO("publish_uartpc: values is empty");
        return;
    }
    const int &size = values.size();
    uint8_t *data = new uint8_t[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = values[i];
    }

    for (int i = 0; i < size; i++)
    {
        if (data[i] == 0x26)
        {
           COUT("dddddddddd")
        }
        
        printf("%02x\n", data[i]);
    }
    delete[] data;
}

void modifyByte3()
{
    uint8_t data[8];
    data[5] |=0x4;
    data[5] |= 0x8;
    printHex(data,8);
}
TestTest::TestTest(/* args */)
{

    modifyByte3();
    
}

void TestTest::thread_Test(float value) 
{
    count++;
    COUT(count);
}

CUSTOMEGISTER(Test, TestTest)
