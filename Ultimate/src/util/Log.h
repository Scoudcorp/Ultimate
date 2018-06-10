#pragma once
#include <cstdarg>
#include <cstdio>

namespace Log {

enum Level {
    Error,
    Warning,
    Info,
    All
};

constexpr void Printf(const Level level, const char * fmt, ...)
{

}

}
