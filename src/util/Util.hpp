#pragma once

#include <string>
#include <vector>

namespace Util
{
std::string LoadAsString(const char* path);
std::vector<std::string> splitString(std::string& str, char denominator);
}; // namespace Util
