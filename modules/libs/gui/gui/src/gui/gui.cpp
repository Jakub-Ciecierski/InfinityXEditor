#include "gui/gui.h"

#include <gui/imgui/impl/imgui_impl_glfw_gl3.h>

namespace ifx {

GUI::GUI(GLFWwindow* window){
    ImGui_ImplGlfwGL3_Init(window, false);
}

GUI::~GUI(){
    ImGui_ImplGlfwGL3_Shutdown();
}

void GUI::NewFrame(){
    ImGui_ImplGlfwGL3_NewFrame();
}

}