#pragma once

#include "fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine{

class Camera2D{
public:
    Camera2D();
    ~Camera2D();

    void init(int width, int height)
    {
        _screen_width = width;
        _screen_height = height;
        _ortho_matrix = glm::ortho(0.0f, (float)_screen_width, 0.0f, (float)_screen_height); 
    }
    void setPosition(glm::vec2 const &pos) {_position = pos; _needs_matrix_update = true;}
    void setScale(float scale) {_scale = scale; _needs_matrix_update = true;}

    glm::vec2 getPosition() {return _position;}
    float getScale() {return _scale;}

    glm::mat4 getCamMatrix() {return _camera_matrix;}

    void update();

    glm::vec2 getScr2w(glm::vec2 const &screen);

private:
    bool _needs_matrix_update;
    float _scale;
    glm::vec2 _position;
    glm::mat4 _camera_matrix ;
    glm::mat4 _ortho_matrix ;

    int _screen_width;
    int _screen_height;
};

}
