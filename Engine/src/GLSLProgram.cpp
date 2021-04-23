#include "GLSLProgram.h"
#include "glad/glad.h"
#include "Log.h"
#include <fstream>

namespace Engine {

GLSLProgram::GLSLProgram()
    :_programID(0)
    ,_fragmentShaderID(0)
    ,_vertexShaderID(0)
    ,_numAttributes(0)
{
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::addAttribute(std::string const &name)
{
    glBindAttribLocation(_programID, _numAttributes++, name.c_str());
}

void GLSLProgram::linkShaders()
{
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    glLinkProgram(_programID);

    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(_programID);

        ERROR("Program failed to link shaders:");
        INFO(&infoLog[0]);
    }

    glDeleteShader(_fragmentShaderID);
    glDeleteShader(_vertexShaderID);
}

void GLSLProgram::compileShaders(std::string const &vertexShaderFile,
                                 std::string const &fragmentShaderFile)
{
    _programID = glCreateProgram();
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER); 
    if (!_vertexShaderID)
        ERROR("Failed to create vertex shader");
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (!_fragmentShaderID)
        ERROR("Failed to create vertex shader");

    compile(vertexShaderFile, _vertexShaderID);
    compile(fragmentShaderFile, _fragmentShaderID);
}

void GLSLProgram::compile(std::string const &filename,  GLuint id)
{
    std::ifstream vertFile(filename);
    if (vertFile.fail())
        ERROR("Failed to open" + filename);

    std::string filecontents = "";
    std::string line;
    while (getline(vertFile, line))
        filecontents += line + "\n";

    const char * contents = filecontents.c_str();
    glShaderSource(id, 1, &contents, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxlength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxlength);
        std::vector<char> error(maxlength);
        glGetShaderInfoLog(id, maxlength, &maxlength, &error[0]); 

        glDeleteShader(id);
        ERROR("Shader failed to compile:" + filename);
        spdlog::error(&error[0]);
    }
}

void GLSLProgram::bind()
{
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) 
        glEnableVertexAttribArray(i);
}

void GLSLProgram::unbind()
{
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) 
        glDisableVertexAttribArray(i);
}

GLuint GLSLProgram::getUniformLocation(std::string const &name) const 
{
    GLint loc = glGetUniformLocation(_programID, name.c_str());
    if (loc == GL_INVALID_INDEX)
        WARN("Uniform "+name+" not found");
    return loc;
}

}
