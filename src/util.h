#ifndef UTIL_H_
#define UTIL_H_

#include <string_view>

namespace util {

template<typename ...Args>
void die(std::string_view message, Args &&...args);

}

#include "util-inl.h"

#endif // UTIL_H_

