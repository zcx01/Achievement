#include "tcp_cache_message.hpp"
#include <algorithm>
#include "tcp_send.hpp"
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
void TcpCacheMessage::addMessage(uint8_t* msgData, int msgLenght)
{
    auto msg = TcpDataAnaly::getMessage(msgData,msgLenght);
    auto msgId = TD::getMessageId(std::get<0>(msg),std::get<1>(msg));
    m_CacheDatas[msgId] = CacheData{std::vector<uint8_t>(msgData,msgData+msgLenght)};
    auto timerId = m_timer->add(RESENDTIME,std::bind(&TcpCacheMessage::timeOut,this,std::placeholders::_1),RESENDTIME);
    m_timerId[msgId] = timerId;
}

bool TcpCacheMessage::onMessageDataAndBodyArrival(MessageData msgData,MessageBody msgBody)
{
    auto msgId = TD::getMessageId(msgData,msgBody);
    m_CacheDatas.erase(msgId);
    m_timerId.erase(msgId);
    return true;
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
    IC_LOG_INFO("%dcount:%d", msgId, (int)m_CacheDatas[msgId].count);
}
