#pragma once

#include "glad/glad.h"
#include <string>
#include "Log.h"
#include <map>

namespace Engine{
 
class GLTexture{
public:
    GLuint id; //all these should be private
    int width;
    int height;

    GLTexture() //for unintialized member data
        :id(0)
        ,width(0)
        ,height(0)
    {
    }

    GLTexture(GLuint id_a, int width_a, int height_a)
        :id(id_a)
        ,width(width_a)
        ,height(height_a)
    {
    }

    static GLTexture create(std::string const & filepath);
    static GLTexture create(int width, int height, std::string const & name);

    void bind();
    void unbind();

private:
    class TextureCache{
    private:
      std::map<std::string, GLTexture> _cache;
    public:
      bool getTexture(std::string const &key, GLTexture &texture) {
        auto tex = _cache.find(key);
        if (tex != _cache.end()) {
          TRACE("Found texture in cache");
          texture = tex->second;
          return true;
        } else {
          TRACE("Not Found in cache");
          return false;
        }
      }

      void insert(std::string const &key, GLTexture const tex)
      {
          TRACE("Inserted in cache");
          _cache.insert(std::make_pair(key, tex));
      }

    };

    static TextureCache _cache;
};

}
