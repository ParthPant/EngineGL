#include "stb_image.h"
#include "GLTexture.h"
#include <string>

namespace Engine{

class ImageLoader
{
public:
    static GLTexture loadPng(std::string const &filepath);
};

}
