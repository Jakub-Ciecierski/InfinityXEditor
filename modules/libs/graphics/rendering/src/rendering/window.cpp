#include "rendering/window.h"
#include "../../../../../../dependencies/glfw-3.1.2/include/GLFW/glfw3.h"

#include <stdexcept>
#include <controls/controls.h>

namespace ifx {

Window::Window(int width, int height, std::string name) :
        width_(width), height_(height), name(name) {
    init();
    setViewport();
}

Window::~Window() {

}

void Window::HandleEvents() {
    Controls& controls = Controls::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_ESCAPE]){
        glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
    }
    if (!keys[GLFW_KEY_LEFT_CONTROL])
        ShowCursor();
    else
        HideCursor();
}

void Window::init() {
    glfwWindow = glfwCreateWindow(width_, height_,
                                  name.c_str(), nullptr, nullptr);
    if (glfwWindow == nullptr) {
        throw new std::invalid_argument("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfwWindow);
}

void Window::setViewport() {
    glfwGetFramebufferSize(glfwWindow, &width_, &height_);

    glViewport(0, 0, width_, height_);
}

int Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::update() {
    HandleEvents();
    glfwPollEvents();
}

GLFWwindow *Window::getHandle() {
    return glfwWindow;
}


void Window::ShowCursor(){
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::HideCursor(){
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

}