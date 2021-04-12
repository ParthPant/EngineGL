#include "IOManager.h"
#include "Log.h"

#include <fstream>

bool IOManager::read_file_to_buffer(std::vector<char> &buffer, std::string const &filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if (file.fail()) {
        ERROR("Failed to open file "+filepath);
        return false;
    }

    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    size -= file.tellg();

    buffer.resize(size);

    file.read(&buffer[0], size);
    file.close();

    return true;
}
