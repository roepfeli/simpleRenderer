#pragma once

#include <string>
#include <vector>

namespace util
{

std::string loadAsString(const char* path);
std::vector<std::string> splitString(std::string& str, char denominator);

}; // namespace util
