#include "{fileName}_item.hpp"
#include "{fileName}_module.hpp"
#include <memory>

{ClassName}Item::{ClassName}Item(std::shared_ptr<{ClassName}Module> module) : module(module)
{
    // register_signals();
}

void {ClassName}Item::subscribe(const std::string &topic)
{
    module->add_item(topic, shared_from_this());
}