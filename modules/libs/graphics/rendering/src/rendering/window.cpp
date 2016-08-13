#include "rendering/window.h"

#include <stdexcept>

namespace ifx {

Window::Window(int width, int height, std::string name) :
        width_(width), height_(height), name(name) {
    init();
    setViewport();
}

Window::~Window() {

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
    glfwPollEvents();
}

GLFWwindow *Window::getHandle() {
    return glfwWindow;
}
}