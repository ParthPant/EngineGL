#include "GLTexture.h"
#include "stb_image.h"
#include "Log.h"

namespace Engine{

GLTexture::TextureCache GLTexture::_cache;

GLTexture GLTexture::create(std::string const &filepath)
{
    GLTexture texture = {0, 0, 0};

    if (_cache.getTexture(filepath, texture)) {
        return texture;
    }

    int width, height, i;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &i, 4); 
    if (!data)
        ERROR("Failed to load image "+filepath);

    texture.width = width;
    texture.height = height;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    _cache.insert(filepath, texture);

    stbi_image_free(data);

    return texture;
}

void GLTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void GLTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
