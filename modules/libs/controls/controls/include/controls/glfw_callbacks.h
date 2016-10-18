#ifndef PROJECT_GLFW_CALLBACKS_H
#define PROJECT_GLFW_CALLBACKS_H

#include <GLFW/glfw3.h>

namespace ifx {

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode);

void mouse_callback(GLFWwindow *window,
                    double xpos, double ypos);

void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods);

void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset);

void char_callback(GLFWwindow* window, unsigned int c);

}
#endif //PROJECT_GLFW_CALLBACKS_H
