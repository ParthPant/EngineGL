#include "Camera2D.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"

namespace Engine{

Camera2D::Camera2D()
    :_position(0.0f, 0.0f)
    ,_camera_matrix(1.0f)
    ,_ortho_matrix(1.0f)
    ,_scale(1.0f)
    ,_needs_matrix_update(true)
    ,_screen_height(500)
    ,_screen_width(500)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::update()
{
    if (_needs_matrix_update)
    {
        _camera_matrix = glm::translate(_ortho_matrix, glm::vec3(-_position.x + _screen_width/2, -_position.y + _screen_height/2, 0.0f));

        glm::vec3 scale = glm::vec3(_scale, _scale, 0.0f);
        _camera_matrix = glm::scale(glm::mat4(1.0f), scale) * _camera_matrix;

        _needs_matrix_update = false;
    }
}

glm::vec2 Camera2D::getScr2w(glm::vec2 const & screen)
{
    glm::vec2 world = screen - glm::vec2(_screen_width/2, _screen_height/2);
    world /= glm::vec2(_scale, _scale);
    world += _position;
    world.y *= -1;

    return world;
}

}
