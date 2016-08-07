#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace ifx {
    /*
     * Windows Context, encapsulating the GLFW handle
     */
    class Window {
    private:
        GLFWwindow *glfwWindow;

        int width;
        int height;
        std::string name;

        void init();
        void setViewport();

    public:

        Window(int width, int height, std::string name);
        ~Window();

        int shouldClose();
        void update();

        GLFWwindow* getHandle();

    };
}

#endif //DUCK_WINDOW_H
