#include "controls/glfw_callbacks.h"

#include <controls/controls.h>

namespace ifx {

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode) {
    Controls& controls = Controls::GetInstance();

    controls.OnKeyboardEvent(action, key);
}

void mouse_callback(GLFWwindow *window,
                    double x, double y) {
    Controls& controls = Controls::GetInstance();

    controls.OnMouseEvent(x, y);
}

void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods) {
    Controls& controls = Controls::GetInstance();

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    controls.OnMouseEvent(xpos, ypos);

    int state_left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int state_right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int state_middle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);

    bool left_pressed = state_left == GLFW_PRESS;
    bool right_pressed = state_right == GLFW_PRESS;
    bool middle_pressed = state_middle == GLFW_PRESS;

    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_LEFT, left_pressed,
                                xpos, ypos);
    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_RIGHT, right_pressed,
                                xpos, ypos);
    controls.OnMouseButtonEvent(MouseButtonType::BUTTON_MIDDLE,
                                middle_pressed,
                                xpos, ypos);
}

void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset) {

}

}