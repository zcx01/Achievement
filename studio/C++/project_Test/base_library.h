#pragma once
#include "commondefine.hpp"
#include "nlohmann/json.hpp"
#include "can/can_api.h"
#include "lin/lin_api.h"

struct IpcMessage
{
    uint32_t length;   /*! 消息长度 */
    uint8_t *data;     /*! 消息内容 */
    bool retain;       /*! 是否保留当前topic最后一次传输的消息内容 Subscriber 上线后可以收到消息 */

#ifdef __cplusplus
    bool operator==(const IpcMessage& other) const
    {
      if(length == other.length && retain == other.retain)
      {
          for(uint32_t i=0; i<length; i++)
          {
              if(data[i] != other.data[i]) 
              {
                  return false;
              }
          }

          return true;
      }

      return false;
    }
#endif //__cplusplus
};


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

namespace fds
{
    template <typename T>
    void SendSingleCanValue(struct veh_signal *sig, T value, uint8_t msg_type = 0, uint8_t sig_count = 1)
    {
        IC_LOG_INFO("send mcu:sigName: %s value: %f, %u", sig->sig_name, value,msg_type);
    }
} // namespace fds

class SendmultiTypeCanValue
{
public:
    template <typename... T>
    void DummyWrapper(T... t){};

    template <typename... Ts>
    void SendCanValue(Ts... args)
    {
        DummyWrapper(deal(args)...);
    }
    template <typename T>
    T deal(T sig_val)
    {
        auto sig = std::get<0>(sig_val);
        auto val = std::get<1>(sig_val);
        IC_LOG_INFO("send mcu:sigName: %s value: %f", sig->sig_name, val);
        return sig_val;
    }
};