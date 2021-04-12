#pragma once

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
    GLuint getUniformLocation(std::string const &name) const;
private:
    GLuint _programID; 

    GLuint _vertexShaderID; 
    GLuint _fragmentShaderID; 
    int _numAttributes;

    void compile(std::string const &filename, GLuint id);
};

}
