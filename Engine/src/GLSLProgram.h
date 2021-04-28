//should this be inside Renderer?
#pragma once

#include "glm.hpp"
#include "glad/glad.h"
#include <string>

namespace Engine {

class GLSLProgram{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(std::string const &vertexShaderFile, std::string const &fragmentShaderFile);
    void linkShaders();
    void bind();
    void unbind();
    void addAttribute(std::string const &name);

    void uploadUniformMat4(std::string const &name, glm::mat4 const &mat)
    {
        uint32_t loc = getUniformLocation(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
    void uploadUniformInt1(std::string const &name, int &integer)
    {
        uint32_t loc = getUniformLocation(name);
        glUniform1i(loc, integer);
    }
    void uploadUniformFloat1(std::string const &name, float &floatpoint)
    {
        uint32_t loc = getUniformLocation(name);
        glUniform1f(loc, floatpoint);
    }
    void uploadUniformFloat3(std::string const &name, glm::vec3 const &vec)
    {
        uint32_t loc = getUniformLocation(name);
        glUniform3fv(loc, 1, &vec[0]);
    }
    GLuint getUniformLocation(std::string const &name) const;
private:
    GLuint _programID; 

    GLuint _vertexShaderID; 
    GLuint _fragmentShaderID; 
    int _numAttributes;

    void compile(std::string const &filename, GLuint id);
};

}
