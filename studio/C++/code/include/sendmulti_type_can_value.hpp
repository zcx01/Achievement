#pragma once
#include <string>
#include "commondefine.hpp"
#define DEFAULT_CTRL_DATA_SIZE (8)
#define DEFAULT_CTRL_FRAME_SIZE (14)
#define DEFAULT_CTRL_DATA_FLAG (0x0A)

namespace fds
{
    template <typename... T>
    void DummyWrapper(T... t){};
} // namespace fds

class SendmultiTypeCanValue
{
public:
    template <typename... Ts>
    void SendCanValue(Ts... args)
    {
        fds::DummyWrapper(cout(args)...);
        uint32_t data_len = sig_count * DEFAULT_CTRL_FRAME_SIZE + 3;
        vehctrl_data = new uint8_t[data_len];
        fds::DummyWrapper(deal(args)...);
        delete[] vehctrl_data;
    }

    template <typename T>
    T cout(T t)
    {
        sig_count++;
        return t;
    }
    template <typename T>
    T deal(T sig_val)
    {
        auto sig = std::get<0>(sig_val);
        auto val = std::get<1>(sig_val);
        // codec_sigle_down_signal_data(sig, val, vehctrl_data + i * DEFAULT_CTRL_FRAME_SIZE, i == 0, 0 , sig_vals.size());
        IC_LOG_INFO(sig,val);
        return sig_val;
    }

    void ini()
    {
        i = 0;
        sig_count = 0;
    }

private:
    int i =0;
    int sig_count = 0;
    uint8_t *vehctrl_data = nullptr;
};


class SendmultiTypeCanValueTest
{
private:
    /* data */
public:
    SendmultiTypeCanValueTest(/* args */);
};

