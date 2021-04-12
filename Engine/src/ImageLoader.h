#include "stb_image.h"
#include "GLTexture.h"
#include <string>

class ImageLoader
{
public:
    static GLTexture loadPng(std::string const &filepath);
};
