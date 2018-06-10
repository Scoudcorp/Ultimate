#include "hudelem.h"
#include <cstdarg>
#include <cstdio>

void hudelem_s::setText(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf_s(buffer, 255, format, args);
    va_end(args);

    this->text = String::LocalizedStringIndex(buffer);
}
