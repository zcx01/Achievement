#include "tcp_cache_message.hpp"
#include <algorithm>
#include "tcp_send.hpp"
#include "tcp_data_analy.hpp"
#include "tcp_data_fill.hpp"

TcpCacheMessage::TcpCacheMessage()
{
    m_timer = new fds::fds_cpp_timer();
    TcpSend::instance().setRecMessageFun(std::bind(&TcpCacheMessage::addMessage,this,std::placeholders::_1,std::placeholders::_2));
}

TcpCacheMessage::~TcpCacheMessage()
{
    delete m_timer;
}

/**
 * 性能优化，可以考虑使用线程
*/
void TcpCacheMessage::addMessage(uint8_t* data, int lenght)
{
    auto msg = TcpDataAnaly::getMessage(data,lenght);
    MessageData msgData = std::get<0>(msg);
    MessageBody msgBody = std::get<1>(msg);
    auto msgId = TcpDataAnaly::getMessageId(msgData.requestId,sizeof(msgData.requestId),msgBody.sid,msgBody.mid);
    m_CacheDatas[msgId] = CacheData{std::vector<uint8_t>(data,data+lenght)};
    auto timerId = m_timer->add(RESENDTIME,std::bind(&TcpCacheMessage::timeOut,this,std::placeholders::_1),RESENDTIME);
    m_timerId[msgId] = timerId;
}

bool TcpCacheMessage::removeId(uint64_t msgId)
{
    m_CacheDatas.erase(msgId);
    m_timerId.erase(msgId);
    return true;
}

bool TcpCacheMessage::onAppDataArrival(uint8_t *app_data, int app_lenght)
{
    if(app_data[0] == 0x3)
    {
        auto reply = TcpDataAnaly::getA35SendReply(app_data,app_lenght);
        auto msgId = TcpDataAnaly::getMessageId(reply.requestId,sizeof(reply.requestId),reply.sid,reply.mid);
        removeId(msgId);
    }
    else if (app_data[0] == 0x00)
    {
        auto msg = TcpDataAnaly::getMessage(app_data, app_lenght);
        MessageData msgData = std::get<0>(msg);
        MessageBody msgBody = std::get<1>(msg);
        auto msgId = TcpDataAnaly::getMessageId(msgData.requestId, sizeof(msgData.requestId), msgBody.sid, msgBody.mid);
        removeId(msgId);
    }
    return false;
}

uint32_t TcpCacheMessage::getType()
{
    return 0x0;
}

void TcpCacheMessage::timeOut(int timerId)
{
    auto timer_Ptr = std::find_if(m_timerId.begin(), m_timerId.end(),
                                  [=](const std::unordered_map<uint64_t, int>::value_type item)
                                  {
                                      return item.second == timerId;
                                  });
    if (timer_Ptr == m_timerId.end())
    {
        m_timer->remove(timerId);
        return;
    }
    uint64_t msgId = (*timer_Ptr).first;
    if(m_CacheDatas.count(msgId) == 0)
    {
        m_timer->remove(timerId);
        return;
    }
    if(m_CacheDatas[msgId].count == 0)
    {
        m_timer->remove(timerId);
        m_CacheDatas.erase(msgId);
        m_timerId.erase(msgId);
        return;
    }
    uint8_t *data = m_CacheDatas[msgId].msgData.data();
    int lenght = m_CacheDatas[msgId].msgData.size();

    TcpDataFill::fillReSendData(data,lenght);
    TcpSend::instance().sendMsg(data, lenght, false);
    m_CacheDatas[msgId].count -= 1;
    IC_LOG_INFO("%lu count:%d", msgId,(int)m_CacheDatas[msgId].count);
}
