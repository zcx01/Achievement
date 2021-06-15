#ifndef {FILENAME}_ITEM_HPP
#define {FILENAME}_ITEM_HPP

#include "base_fds_item.hpp"

using std::string;

class {ClassName}Module;

class {ClassName}Item : public BaseFdsItem
{
public:
    using BaseFdsItem::BaseFdsItem;
    int status;
	
};

#endif // !{FILENAME}_ITEM_HPP
