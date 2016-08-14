#include "rendering/renderer.h"
#include <controls/glfw_callbacks.h>

#include <stdexcept>
#include <controls/controls.h>

namespace ifx {

Renderer::Renderer() :
    scene_(nullptr) {
    initGLFWRenderContext();
    initOpenGLContext();
    initGLFWCallbacks();
}

Renderer::~Renderer(){
    delete scene_;
    delete window_;
}

void Renderer::startMainLoop(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!window_->shouldClose()) {
        Update();
        Render();

        glfwSwapBuffers(window_->getHandle());
    }

    glfwTerminate();
}

Scene* Renderer::SetScene(Scene* scene){
    Scene* prev_scene = scene_;
    scene_ = scene;

    return prev_scene;
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
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->render();
}

}