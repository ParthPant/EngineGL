#pragma once

#include <vector>
#include <string>

namespace Engine{

class IOManager{
public:
    static bool read_file_to_buffer(std::vector<char> &buffer, std::string const &filepath);
private:
};

}
