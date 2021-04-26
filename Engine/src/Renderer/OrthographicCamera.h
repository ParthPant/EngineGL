#pragma once

#include "glm.hpp"

namespace Engine{

class OrthographicCamera{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void setPosition(glm::vec3 const &position)
    {
        _position = position;
        recalculateViewMatrix();
    }
    void setRotation(float rotation)
    { 
        _rotation = rotation;
        recalculateViewMatrix();
    }

    glm::vec3 getPosition() {return _position;}
    float getRotation() {return _rotation;}

    glm::mat4& getViewProjectionMatrix() {return _viewProjection;}
    glm::mat4& getViewMatrix() {return _view;}
    glm::mat4& getProjectionMatrix() {return _projection;}

private:
    void recalculateViewMatrix();

    glm::mat4 _projection;
    glm::mat4 _view;
    glm::mat4 _viewProjection;

    glm::vec3 _position;
    float _rotation;
};

}
