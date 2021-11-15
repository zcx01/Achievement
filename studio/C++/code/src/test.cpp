#include "test.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

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

TestTest::TestTest(/* args */) 
{
    std::string content = "{\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":[1,2,3]}";
    nlohmann::json j = nlohmann::json::parse(content);
    PayloadInfo info = j.get<PayloadInfo>();
    std::vector<int> value =info.value.get<std::vector<int>>();
    COUTI(value);
    
    content = "{\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":1}";
    j = nlohmann::json::parse(content);
    info = j.get<PayloadInfo>();
    int in = info.value.get<int>();
    COUT(in)
}

CUSTOMEGISTER(Test,TestTest)