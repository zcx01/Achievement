#ifndef TEXT_TIP_ADAPTER_TEXT
#define TEXT_TIP_ADAPTER_TEXT
#include "text_tip_adapter.hpp"

class TextTipAdapterTest
{
public:
    TextTipAdapterTest();
private:

    void OneTest();

    void sendWarnInfo(const WarnInfo &info);

    void addWarn(std::string topic, int value);

    void COUT_Topic();

    void add_Test_Topic();

    bool is_one_finish = true;

    TextTipAdapter d;
};
#endif // TEXT_TIP_ADAPTER_TEXT
