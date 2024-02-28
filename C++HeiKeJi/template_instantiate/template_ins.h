#pragma once

#include <string>
#include <variant>


using Object = std::variant<int, double, std::string>;

void add_object(Object o);
void print_objects();
