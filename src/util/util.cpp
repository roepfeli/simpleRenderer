#include <util.hpp>

#include <fstream>
#include <iostream>

#include <string>
#include <vector>

namespace util
{

std::string loadAsString(const char* path)
{
    std::ifstream file;
    file.open(path, std::ios::in);

    if (!file.is_open())
    {
        return std::string("");
    }

    std::string content("");
    std::string line;

    while (std::getline(file, line))
    {
        content += line + '\n';
    }

    file.close();

    return content;
}

std::vector<std::string> splitString(std::string& str, char denominator)
{
    std::vector<std::string> splits;

    std::string tmp;
    for (char i : str)
    {
        if (i == denominator)
        {
            if (tmp.size() > 0)
            {
                splits.push_back(tmp);
            }
            tmp = "";
        }

        else
        {
            tmp.push_back(i);
        }
    }

    splits.push_back(tmp);

    return splits;
}

} // namespace util