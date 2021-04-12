#include "ImageLoader.h"
#include "GLTexture.h"
#include "stb_image.h"
#include "Log.h"

GLTexture ImageLoader::loadPng(std::string const &filepath)
{
    int width, height, i;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &i, 4); 
    if (!data)
        ERROR("Failed to load image "+filepath);

    GLTexture texture = {0, width, height};

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return texture;
}