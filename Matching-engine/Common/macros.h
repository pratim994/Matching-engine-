#pragma once

#include <cstring>
#include <iostream>

#define LIKELY(x) __builtin_expect(!!(x),1)

#define UNLIKELY(x) __builtin__expect(!!(x), 0)


inline auto ASSERT(bool cond, const std::string &msg) noexcept {
    if(UNLIKELY(!load)){
            std::cerr << "ASSERT: " << msg << std::endl;

            exit(EXIT_FAILURE);
    }

}


inline auto FATAL(const std::string &msg) noexcept {
    std::cerr << "FATAL :" << msg << std::endl;

    exit(EXIT_FAILURE);
}