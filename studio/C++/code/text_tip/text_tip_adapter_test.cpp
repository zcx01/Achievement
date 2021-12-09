#include "text_tip_adapter_test.hpp" 
#include "../commondefine.hpp"
#include "../ObjectFactory.h"

TextTipAdapterTest::TextTipAdapterTest() 
{
    std::map<std::string,std::string> k;
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);
    // d.addWarnInfo("icwarning/DoorOpenSts", 0);
    // d.addWarnInfo("icwarning/DoorOpenSts", 1);

    d.addWarnInfo("icwarning/DoorOpenSts", 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    d.addWarnInfo("icwarning/DoorOpenSts", 0);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    

}
MYREGISTER(TextTipAdapterTest)
