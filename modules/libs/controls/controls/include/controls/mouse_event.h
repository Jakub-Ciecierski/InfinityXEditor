#ifndef PROJECT_MOUSE_EVENT_H
#define PROJECT_MOUSE_EVENT_H

namespace ifx {

enum class MouseButtonType {
    BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE
};

class MouseEvent {
public:
    MouseEvent(MouseButtonType type);

    ~MouseEvent();

    MouseButtonType type() { return type_; }
    bool is_pressed() { return is_pressed_; }
    float x() {return x_;}
    float y() {return y_;}

    bool is_pressed(bool pressed) { is_pressed_ = pressed; }
    void x(float x) {x_ = x;}
    void y(float y) {y_ = y;}

private:
    MouseButtonType type_;

    bool is_pressed_;

    float x_;
    float y_;
};

struct MouseEvents{
    enum class MouseButtonType;
    MouseEvents() :
            LeftMouse(nullptr),
            RightMouse(nullptr),
            MiddleMouse(nullptr),
            pos_x(0), pos_y(0),
            prev_pos_x(0), prev_pos_y(0){
    }
    ~MouseEvents(){
        if(LeftMouse != nullptr)
            delete LeftMouse;
        if(RightMouse != nullptr)
            delete RightMouse;
        if(MiddleMouse != nullptr)
            delete MiddleMouse;
    }
    MouseEvent* LeftMouse;
    MouseEvent* RightMouse;
    MouseEvent* MiddleMouse;

    float pos_x;
    float pos_y;

    float prev_pos_x;
    float prev_pos_y;
};

}

#endif //PROJECT_MOUSE_EVENT_H
