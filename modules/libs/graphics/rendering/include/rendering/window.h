#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace ifx {
/*
 * Windows Context, encapsulating the GLFW handle
 */
class Window {

public:
    Window(int width, int height, std::string name);
    ~Window();

    int* width() {return &width_;}
    int* height() {return &height_;}

    int shouldClose();
    void update();

    GLFWwindow* getHandle();

private:
    GLFWwindow* glfwWindow;

    int width_;
    int height_;
    std::string name;

    void init();
    void setViewport();
};
}

#endif //DUCK_WINDOW_H
