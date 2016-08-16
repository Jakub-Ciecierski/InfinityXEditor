#include "rendering/fbo_rendering/fbo_renderer.h"

#include <math/math_ifx.h>
#include <shaders/buffers/fbo.h>
#include <model/mesh.h>
#include <shaders/textures/texture_loader.h>
#include <rendering/window.h>

namespace ifx {

FBORenderer::FBORenderer(Window* window) :
        program_(nullptr){
    initFBO(window);
    initScreenMesh();
}

FBORenderer::~FBORenderer(){
    delete fbo_;
    delete screenMesh_;
    if(program_ != nullptr)
        delete program_;
}

void FBORenderer::SetProgram(Program* program){
    if(program_ != nullptr) delete program_;
    program_ = program;
}

void FBORenderer::Bind(){
    fbo_->bind();
}

void FBORenderer::Render(){
    Render(program_);
}

void FBORenderer::Render(Program* program){
    if (program_ == nullptr) return;

    fbo_->unbind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screenMesh_->draw(*program);
}

void FBORenderer::initFBO(Window* window){
    Texture texture = TextureLoader().CreateEmptyTexture(TextureTypes::FBO,
                                                         *(window->width()),
                                                         *(window->height()));
    fbo_ = new FBO(texture);
    fbo_->compile();
}

void FBORenderer::initScreenMesh(){
    // The position is in Normalized Device Coordinates.
    std::vector <Vertex> vertices = {
            Vertex{glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, -1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, -1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
    };
    std::vector <GLuint> indices = { 0, 1, 3, 1, 2, 3 };

    std::vector <Texture> textures {fbo_->texture()};

    screenMesh_ = new Mesh(vertices, indices, textures);
}

}
