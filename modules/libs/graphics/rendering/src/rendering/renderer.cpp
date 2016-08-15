#include "rendering/renderer.h"

#include <controls/glfw_callbacks.h>
#include <controls/controls.h>
#include <rendering/fbo_rendering/fbo_renderer.h>
#include <stdexcept>

namespace ifx {

Renderer::Renderer() :
    scene_(nullptr),
    rendering_type_(RenderingType::NORMAL),
    fbo_renderer_(nullptr){
    initGLFWRenderContext();
    initOpenGLContext();
    initGLFWCallbacks();
}

Renderer::~Renderer(){
    delete scene_;
    delete window_;

    if(fbo_renderer_ != nullptr)
        delete fbo_renderer_;
}

void Renderer::startMainLoop(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!window_->shouldClose()) {
        HandleEvents();
        Update();
        Render();

        glfwSwapBuffers(window_->getHandle());
    }

    glfwTerminate();
}

void Renderer::HandleEvents() {
    Controls& controls = Controls::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_R]){
        scene_->ReloadProgams();
        if(fbo_renderer_->program())
            fbo_renderer_->program()->Reload();
    }
    if (keys[GLFW_KEY_F1]){
        rendering_type_ = RenderingType::NORMAL;
    }
    if (keys[GLFW_KEY_F2]){
        rendering_type_ = RenderingType::FBO_TEXTURE;
    }
}

Scene* Renderer::SetScene(Scene* scene){
    Scene* prev_scene = scene_;
    scene_ = scene;

    return prev_scene;
}

void Renderer::SetRenderingType(RenderingType type){
    rendering_type_ = type;
}

void Renderer::SetFBORenderer(FBORenderer* fbo_renderer){
    if(fbo_renderer_ != nullptr)
        delete fbo_renderer_;
    fbo_renderer_ = fbo_renderer;
}

void Renderer::initGLFWRenderContext(){
    glfwInit();
    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int width = 1200;
    int height = 800;
    window_ = new Window(width, height, "Tessellation");
}

void Renderer::initOpenGLContext(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        throw new std::invalid_argument("Failed to initialize GLEW");
    }
}

void Renderer::initGLFWCallbacks(){
    glfwSetKeyCallback(window_->getHandle(), key_callback);
    glfwSetCursorPosCallback(window_->getHandle(), mouse_callback);
    glfwSetMouseButtonCallback(window_->getHandle(), mouse_button_callback);
    glfwSetScrollCallback(window_->getHandle(), mousescroll_callback);
}

void Renderer::Update(){
    window_->update();
    scene_->update();
    Controls::GetInstance().Update();
}

void Renderer::Render(){
    if(rendering_type_ == RenderingType::NORMAL)
        RenderNormal();
    if(rendering_type_ == RenderingType::FBO_TEXTURE)
        RenderFBOTexture();
}

void Renderer::RenderNormal(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    scene_->render();
}

void Renderer::RenderFBOTexture(){
    if(fbo_renderer_ == nullptr)
        return;
    // First Pass
    fbo_renderer_->Bind();
    RenderNormal();

    // Second Pass
    glDisable(GL_DEPTH_TEST);
    fbo_renderer_->Render();
}

}