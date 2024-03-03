#include "util.h"

#include <stdio.h>
#include <stdlib.h>

namespace util {

template<typename ...Args>
void die(std::string_view message, Args &&...args) {
    fprintf(stderr, "Error: ");
    fprintf(stderr, message.data(), args...);
    putchar('\n');
    exit(-1);
}

}
