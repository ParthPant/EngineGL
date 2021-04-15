#include "SpriteBatch.h"
#include "Log.h"
#include "glm/glm.hpp"
#include <algorithm>

namespace Engine{

SpriteBatch::SpriteBatch()
    :_vbo(0)
    ,_vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
    _glyphs.clear();
    _glyphptrs.clear();
}

void SpriteBatch::init()
{
    createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sort_type)
{
    _sort_type = sort_type;
    //for (Glyph *glyph : _glyphs)
        //delete(glyph);

    _render_batches.clear();
    _glyphs.clear();
    _glyphptrs.clear();
}

void SpriteBatch::end()
{
    _glyphptrs.resize(_glyphs.size());
    for(int i = 0; i<_glyphs.size(); i++)
        _glyphptrs[i] = &_glyphs[i];

    sortGlyphs();
    createRenderBatches();
}

void SpriteBatch::renderBatch()
{
    glBindVertexArray(_vao);
    for(int i=0; i<_render_batches.size(); i++)
    {
        if(_render_batches[i]._texture)
            glBindTexture(GL_TEXTURE_2D, _render_batches[i]._texture);
        //Log::TRACE("DrawCall with {} vertices", _render_batches[i]._num_vertices);
        glDrawArrays(GL_TRIANGLES, _render_batches[i]._offset, _render_batches[i]._num_vertices); 
    }
    glBindVertexArray(0);
}

void SpriteBatch::draw(glm::vec4 const &destRect,
                       glm::vec4 const &uvrect,
                       float const depth,
                       GLuint const texture,
                       Color const &color)
{
    _glyphs.emplace_back(destRect, uvrect, depth, texture, color);
}

void SpriteBatch::createVertexArray()
{
    if (!_vao)
        glGenVertexArrays(1, &_vao);

    if (!_vbo)
        glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
    switch (_sort_type) {
        case GlyphSortType::NONE:
        case GlyphSortType::TEXTURE:
            std::stable_sort(_glyphptrs.begin(), _glyphptrs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->texture < b->texture;});
            break;
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphptrs.begin(), _glyphptrs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->depth < b->depth;});
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphptrs.begin(), _glyphptrs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->depth > b->depth;});
            break;
    }
}

void SpriteBatch::createRenderBatches()
{
    if (_glyphs.empty())
        return;

    std::vector<Vertex> vertices;
    vertices.resize(_glyphptrs.size() * 6);
    
    int curr_vert = 0;
    int offset = 0;
    
    _render_batches.emplace_back(offset, _glyphptrs[0]->texture, 6);
    vertices[curr_vert++] = _glyphptrs[0]->topright;
    vertices[curr_vert++] = _glyphptrs[0]->topleft;
    vertices[curr_vert++] = _glyphptrs[0]->bottomleft;
    vertices[curr_vert++] = _glyphptrs[0]->bottomleft;
    vertices[curr_vert++] = _glyphptrs[0]->bottomright;
    vertices[curr_vert++] = _glyphptrs[0]->topright;

    offset += 6;

    for (int curr_glyph = 1; curr_glyph < _glyphptrs.size(); curr_glyph++)
    {
        if (_glyphptrs[curr_glyph]->texture != _glyphptrs[curr_glyph-1]->texture)
            _render_batches.emplace_back(offset, _glyphptrs[curr_glyph]->texture, 6);
        else
            _render_batches.back()._num_vertices += 6;

        vertices[curr_vert++] = _glyphptrs[curr_glyph]->topright;
        vertices[curr_vert++] = _glyphptrs[curr_glyph]->topleft;
        vertices[curr_vert++] = _glyphptrs[curr_glyph]->bottomleft;
        vertices[curr_vert++] = _glyphptrs[curr_glyph]->bottomleft;
        vertices[curr_vert++] = _glyphptrs[curr_glyph]->bottomright;
        vertices[curr_vert++] = _glyphptrs[curr_glyph]->topright;

        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // orphan buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // add data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteBatch::RenderBatch::RenderBatch(GLuint offset, GLuint texture, GLuint num_vertices)
    :_offset(offset)
    ,_texture(texture)
    ,_num_vertices(num_vertices)
{
}

SpriteBatch::Glyph::Glyph(glm::vec4 const &destRect,
                   glm::vec4 const &uvrect,
                   float const a_depth,
                   GLuint const a_texture,
                   Color const &color)
{
    texture = a_texture;
    depth = a_depth;

    topright.color = color;
    topleft.color = color;
    bottomleft.color = color;
    bottomright.color = color;

    topright.setPosition   (destRect.x + destRect.z, destRect.y + destRect.w);
    topright.setUV         (uvrect.x + uvrect.z    , uvrect.y + uvrect.w);

    topleft.setPosition    (destRect.x             , destRect.y + destRect.w);
    topleft.setUV          (uvrect.x               , uvrect.y + uvrect.w);

    bottomleft.setPosition (destRect.x             , destRect.y);
    bottomleft.setUV       (uvrect.x               , uvrect.y);

    bottomright.setPosition(destRect.x + destRect.z, destRect.y);
    bottomright.setUV      (uvrect.x + uvrect.z    , uvrect.y);
}

}
