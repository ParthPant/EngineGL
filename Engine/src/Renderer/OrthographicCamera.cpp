#include "OrthographicCamera.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "matrix.hpp"

namespace Engine{

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    :_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
    ,_view(glm::mat4(1.0f))
    ,_rotation(0.0f)
    ,_position({0,0,0})
{
    _viewProjection = _projection * _view;
}

void OrthographicCamera::recalculateViewMatrix()
{
    glm::mat4 transformation = glm::translate(glm::mat4(1.0f), _position) *
                               glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3(0,0,1));
    
    _view = glm::inverse(transformation);
    _viewProjection = _projection * _view;
}

}
