#include <iostream>
#include "controls/controls.h"

namespace ifx {

Controls::Controls() {
    control_mode_ = ControlMode::SCENE;

    mouse_events_.LeftMouse = new MouseEvent(MouseButtonType::BUTTON_LEFT);
    mouse_events_.RightMouse = new MouseEvent(MouseButtonType::BUTTON_RIGHT);
    mouse_events_.MiddleMouse = new MouseEvent(MouseButtonType::BUTTON_MIDDLE);

    keyboard_keys_.resize(1024);
}

Controls::~Controls() {
}

Controls& Controls::GetInstance(){
    static Controls controls;
    return controls;
}

void Controls::OnKeyboardEvent(int action, int key){
    if (key >= 0 && key < keyboard_keys_.size()) {
        if (action == GLFW_PRESS) {
            keyboard_keys_[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyboard_keys_[key] = false;
        }
    }
}

void Controls::OnMouseButtonEvent(MouseButtonType type, bool is_pressed,
                                  float xpos, float ypos) {
    MouseEvent* current_event = nullptr;
    if (mouse_events_.LeftMouse->type() == type)
        current_event = mouse_events_.LeftMouse;
    if (mouse_events_.RightMouse->type() == type)
        current_event = mouse_events_.RightMouse;
    if (mouse_events_.MiddleMouse->type() == type)
        current_event = mouse_events_.MiddleMouse;

    if(current_event == nullptr)
        return;

    current_event->is_pressed(is_pressed);
    current_event->x(xpos);
    current_event->y(ypos);
}

void Controls::OnMouseEvent(float xpos, float ypos){
    mouse_events_.pos_x = xpos;
    mouse_events_.pos_y = ypos;
}

void Controls::SetControlMode(ControlMode control_mode){
    control_mode_ = control_mode;
}

void Controls::Update(){
    mouse_events_.prev_pos_x = mouse_events_.pos_x;
    mouse_events_.prev_pos_y = mouse_events_.pos_y;
}


}