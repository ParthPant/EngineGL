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
    for (Glyph *glyph : _glyphs)
        delete(glyph);
    _glyphs.clear();
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
}

void SpriteBatch::end()
{
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
    Glyph *newGlyph = new Glyph;
    newGlyph->texture = texture;
    newGlyph->depth = depth;

    newGlyph->topright.color = color;
    newGlyph->topleft.color = color;
    newGlyph->bottomleft.color = color;
    newGlyph->bottomright.color = color;

    newGlyph->topright.setPosition   (destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph->topright.setUV         (uvrect.x + uvrect.z    , uvrect.y + uvrect.w);

    newGlyph->topleft.setPosition    (destRect.x             , destRect.y + destRect.w);
    newGlyph->topleft.setUV          (uvrect.x               , uvrect.y + uvrect.w);

    newGlyph->bottomleft.setPosition (destRect.x             , destRect.y);
    newGlyph->bottomleft.setUV       (uvrect.x               , uvrect.y);

    newGlyph->bottomright.setPosition(destRect.x + destRect.z, destRect.y);
    newGlyph->bottomright.setUV      (uvrect.x + uvrect.z    , uvrect.y);

    _glyphs.push_back(newGlyph);
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
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->texture < b->texture;});
            break;
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->depth < b->depth;});
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                            [](Glyph*a, Glyph*b)->bool{return a->depth > b->depth;});
            break;
    }
}

void SpriteBatch::createRenderBatches()
{
    if (_glyphs.empty())
        return;

    std::vector<Vertex> vertices;
    vertices.resize(_glyphs.size() * 6);
    
    int curr_vert = 0;
    int offset = 0;
    
    _render_batches.emplace_back(offset, _glyphs[0]->texture, 6);
    vertices[curr_vert++] = _glyphs[0]->topright;
    vertices[curr_vert++] = _glyphs[0]->topleft;
    vertices[curr_vert++] = _glyphs[0]->bottomleft;
    vertices[curr_vert++] = _glyphs[0]->bottomleft;
    vertices[curr_vert++] = _glyphs[0]->bottomright;
    vertices[curr_vert++] = _glyphs[0]->topright;

    offset += 6;

    for (int curr_glyph = 1; curr_glyph < _glyphs.size(); curr_glyph++)
    {
        if (_glyphs[curr_glyph]->texture != _glyphs[curr_glyph-1]->texture)
            _render_batches.emplace_back(offset, _glyphs[curr_glyph]->texture, 6);
        else
            _render_batches.back()._num_vertices += 6;

        vertices[curr_vert++] = _glyphs[curr_glyph]->topright;
        vertices[curr_vert++] = _glyphs[curr_glyph]->topleft;
        vertices[curr_vert++] = _glyphs[curr_glyph]->bottomleft;
        vertices[curr_vert++] = _glyphs[curr_glyph]->bottomleft;
        vertices[curr_vert++] = _glyphs[curr_glyph]->bottomright;
        vertices[curr_vert++] = _glyphs[curr_glyph]->topright;

        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // orphan buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // add data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

RenderBatch::RenderBatch(GLuint offset, GLuint texture, GLuint num_vertices)
    :_offset(offset)
    ,_texture(texture)
    ,_num_vertices(num_vertices)
{
}

}
