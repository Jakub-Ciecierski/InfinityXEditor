#include "rendering/window.h"

#include <stdexcept>

using namespace ifc;

Window::Window(int width, int height, std::string name):
    width(width), height(height), name(name){

    init();
    setViewport();
}

Window::~Window() {

}

void Window::init() {
    glfwWindow = glfwCreateWindow(width, height,
                                          name.c_str(), nullptr, nullptr);
    if (glfwWindow == nullptr){
        throw new std::invalid_argument("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfwWindow);
}

void Window::setViewport() {
    glfwGetFramebufferSize(glfwWindow, &width, &height);

    glViewport(0, 0, width, height);
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
