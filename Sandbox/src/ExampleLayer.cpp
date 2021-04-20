#include "ExampleLayer.h"
#include "Application.h"
#include "Engine.h"
#include "GLTexture.h"
#include "Log.h"

void ExampleLayer::onAttach()
{
    _spriteBatch.init();
    _program.compileShaders("/home/parth/dev/opengl/Sandbox/res/shaders/colorshading.vert",
                            "/home/parth/dev/opengl/Sandbox/res/shaders/colorshading.frag");

    _program.addAttribute("vertexPosition");
    _program.addAttribute("vertexColor");
    _program.addAttribute("vertexUV");
    _program.linkShaders();

    _texture = Engine::GLTexture::create("/home/parth/dev/opengl/Sandbox/res/textures/ethereum.png");

    int width = Engine::Application::getApplication()->getWindow()->getScreenWidth();
    int height = Engine::Application::getApplication()->getWindow()->getScreenHeight();
    _camera.init(width, height);
}

void ExampleLayer::onUpdate()
{
    _camera.update();

    _program.bind();

    glm::mat4 P = _camera.getCamMatrix();
    GLint uniform_p = _program.getUniformLocation("P");
    glUniformMatrix4fv(uniform_p, 1, GL_FALSE, &P[0][0]);

    glActiveTexture(GL_TEXTURE0);
    GLint sampler = _program.getUniformLocation("sampler");
    glUniform1i(sampler, 0);

    _spriteBatch.begin();
    
    _spriteBatch.draw(glm::vec4(0, 0, 500, 500), glm::vec4(0, 0, 1, 1), 0, _texture.id, {255, 255, 255, 255});

    _spriteBatch.end();

    _texture.unbind();
    _spriteBatch.renderBatch();
    _program.unbind();
}

void ExampleLayer::onDetach()
{
    Engine::TRACE("{} detached", _name);
}

void ExampleLayer::onEvent(Engine::Event &e)
{
    Engine::TRACE(e.toString());
}
