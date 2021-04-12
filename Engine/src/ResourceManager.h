#pragma once

#include "GLTexture.h"
#include "TextureCache.h"
#include <string>
#include <map>

namespace Engine{

class ResourceManager{
public:
    static GLTexture getTexture (std::string filepath)
        {
            return _textureCache.getTexture(filepath);
        }
private:
    static TextureCache _textureCache;
};

}
