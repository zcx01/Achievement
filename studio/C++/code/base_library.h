#pragma once
#include "commondefine.hpp"

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
