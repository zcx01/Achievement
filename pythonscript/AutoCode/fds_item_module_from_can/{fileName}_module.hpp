#ifndef  {FILENAME}_MODULE_HPP
#define {FILENAME}_MODULE_HPP

#include <memory>
#include "base_fds_module.hpp"

class {ClassName}Module final: public BaseFdsModule
{

private:
    void link_signal_item();

    //std::shared_ptr<AirConditioner> air_conditioner = nullptr;
};

#endif // !{FILENAME}_MODULE_HPP
