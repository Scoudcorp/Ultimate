#include "StringUtil.h"
#include "iw4/iw_string.h"
#include <cstdarg>
#include <iterator>

std::vector<std::string> StringSplit(const std::string& string, const char delimeter)
{
    std::vector<std::string> elems;
    StringSplit(string, delimeter, std::back_inserter(elems));
    return elems;
}

namespace Util {

const char* HostFormat(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    auto const result = String::Format("^2MW2LT^7: %s", String::Format(format, args));

    va_end(args);

    return result;
}
}
