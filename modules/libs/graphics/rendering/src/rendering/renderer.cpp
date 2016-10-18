#include "rendering/renderer.h"

#include <controls/glfw_callbacks.h>
#include <controls/controls.h>
#include <rendering/fbo_rendering/fbo_renderer.h>
#include <gui/gui.h>
#include <gui/imgui/imgui.h>

namespace ifx {

Renderer::Renderer() :
    scene_(nullptr),
    rendering_type_(RenderingType::NORMAL),
    fbo_renderer_(nullptr){
    initGLFWRenderContext();
    initOpenGLContext();
    initGLFWCallbacks();
}

Renderer::~Renderer(){}

void Renderer::HandleEvents() {
    Controls& controls = Controls::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_R]){
        scene_->ReloadProgams();
        if(fbo_renderer_->program())
            fbo_renderer_->program()->Reload();
    }
    if (keys[GLFW_KEY_1]){
        rendering_type_ = RenderingType::NORMAL;
    }
    if (keys[GLFW_KEY_2]){
        rendering_type_ = RenderingType::FBO_TEXTURE;
    }
}

void Renderer::SetScene(std::unique_ptr<Scene> scene){
    scene_ = std::move(scene);
}

void Renderer::SetGUI(std::unique_ptr<GUI> gui){
    gui_ = std::move(gui);
}

void Renderer::SetRenderingType(RenderingType type){
    rendering_type_ = type;
}

void Renderer::SetShadowsType(ShadowsType type){
    shadow_type_ = type;
}

void Renderer::SetFBORenderer(std::unique_ptr<FBORenderer> fbo_renderer){
    fbo_renderer_ = std::move(fbo_renderer);
}

void Renderer::SetShadowMapping(ShadowMapping* shadow_mapping){
    shadow_mapping_.reset(shadow_mapping);
}

void Renderer::initGLFWRenderContext(){
    glfwInit();
    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int width = 1400;
    int height = 900;
    window_ .reset(new Window(width, height, "InfinityX"));
}

void Renderer::initOpenGLContext(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw new std::invalid_argument("Failed to initialize GLEW");
}

void Renderer::initGLFWCallbacks(){
    glfwSetKeyCallback(window_->getHandle(), key_callback);
    glfwSetCursorPosCallback(window_->getHandle(), mouse_callback);
    glfwSetMouseButtonCallback(window_->getHandle(), mouse_button_callback);
    glfwSetScrollCallback(window_->getHandle(), mousescroll_callback);
    glfwSetCharCallback(window_->getHandle(), char_callback);
}

void Renderer::Update(){
    window_->update();
    scene_->update();
    Controls::GetInstance().Update();
}

void Renderer::Render(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(rendering_type_ == RenderingType::NORMAL)
        RenderNormal();
    if(rendering_type_ == RenderingType::FBO_TEXTURE)
        RenderFBOTexture();

    if(gui_){
        gui_->Render();
    }

    glfwSwapBuffers(window_->getHandle());
}

void Renderer::RenderNormalShadowMapping(){
    shadow_mapping_->Render(scene_.get());

    glViewport(0, 0, *(window_->width()), *(window_->height()));
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    scene_->render();
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