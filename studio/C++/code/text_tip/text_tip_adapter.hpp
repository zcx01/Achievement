#ifndef TEXT_TIP_ADAPTER
#define TEXT_TIP_ADAPTER
#include <unordered_map>
#include <string>
#include <algorithm>
#include "nlohmann/json.hpp"
#include "text_warn_rule_manage.hpp"

class TextTipAdapter 
{
public:
    TextTipAdapter();

    std::unordered_map<std::string,nlohmann::json> getData(const std::string & topic);

    void addWarnInfo(std::string topic, int value);

private:
    void sendWarnInfo(const WarnInfo &info);

    std::unordered_map<std::string, std::unordered_map<std::string,nlohmann::json> > m_data;
    TextWarnRuleManage m_rule;
};

#endif // TEXT_TIP_ADAPTER
