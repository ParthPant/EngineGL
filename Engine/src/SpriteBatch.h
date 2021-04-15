#pragma once

#include "fwd.hpp"
#include "glad/glad.h"
#include "Sprite.h"
#include <vector>

namespace Engine{

class SpriteBatch{
private:

    class Glyph{
    public:
        GLuint texture;

        float depth;

        Vertex topleft;
        Vertex topright;
        Vertex bottomleft;
        Vertex bottomright;

        Glyph(glm::vec4 const &destRect,
              glm::vec4 const &uvrect,
              float const a_depth,
              GLuint const a_texture,
              Color const &color);
    };

    class RenderBatch{
    public:
        GLuint _offset;
        GLuint _texture;
        GLuint _num_vertices;

        RenderBatch(GLuint offset, GLuint texture, GLuint _num_vertices);
    };

    void createVertexArray();
    
    GLuint _vbo;
    GLuint _vao;

    std::vector<Glyph*> _glyphptrs;
    std::vector<Glyph> _glyphs;

    enum class GlyphSortType{
        NONE,
        FRONT_TO_BACK,        
        BACK_TO_FRONT,
        TEXTURE
    } _sort_type;

    void sortGlyphs();

    std::vector<RenderBatch> _render_batches;
    void createRenderBatches();

public:
    SpriteBatch();
    ~SpriteBatch();

    void init();
    void begin(GlyphSortType sort_type = GlyphSortType::TEXTURE);
    void end();
    void draw(glm::vec4 const &destRect, glm::vec4 const &uvrect, float const depth, GLuint const texture, Color const &color);
    void renderBatch();
};

}
