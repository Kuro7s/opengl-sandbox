#pragma once

#include <string_view>

namespace util
{

template<typename ...Args>
void die(std::string_view message, Args&&... args);

}

#include "util.inl"
