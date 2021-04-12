#include "TextureCache.h"
#include "GLTexture.h"
#include "ImageLoader.h"
#include "Log.h"

#include <utility>

GLTexture TextureCache::getTexture(std::string const &filepath)
{
    auto tex = _cache.find(filepath);
    if (tex != _cache.end()) {
        //TRACE("Found texture in cache");
        return tex->second;
    } else {
        GLTexture texture = ImageLoader::loadPng(filepath);
        _cache.insert(std::make_pair(filepath, texture));
        //TRACE("texture loaded and cached");
        return texture;
    }
}
