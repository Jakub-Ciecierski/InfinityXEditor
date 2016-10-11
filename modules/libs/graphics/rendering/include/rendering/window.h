#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>

#include <GLFW/glfw3.h>
#include <controls/event_handler.h>

namespace ifx {
/*
 * Windows Context, encapsulating the GLFW handle
 */
class Window : public EventHandler {

public:
    Window(int width, int height, std::string name);
    ~Window();

    int* width() {return &width_;}
    int* height() {return &height_;}

    void Terminate();

    // Overridden from EvenHandler
    void HandleEvents() override;

    int shouldClose();
    void update();

    GLFWwindow* getHandle();

    void ShowCursor();
    void HideCursor();

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
