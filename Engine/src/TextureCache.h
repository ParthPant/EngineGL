#pragma once

#include "GLTexture.h"

#include <map>
#include <string>

class TextureCache{
public:
    GLTexture getTexture(std::string const &filepath);
private:
    std::map<std::string, GLTexture> _cache;
};