#pragma once

#include <sstream>
#include <string>
#include <vector>

template <typename Out>
void StringSplit(const std::string& string, const char delimeter, Out result)
{
    std::stringstream ss(string);
    std::string item;
    while (std::getline(ss, item, delimeter)) {
        *(result++) = item;
    }
}

std::vector<std::string> StringSplit(const std::string& string, char delimeter);

namespace Util
{
	const char *HostFormat(const char* format, ...);
}
