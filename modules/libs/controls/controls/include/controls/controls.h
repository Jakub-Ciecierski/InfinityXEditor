#ifndef PROJECT_CONTROLS_H
#define PROJECT_CONTROLS_H

#include <controls/mouse_event.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace ifx {

/**
 * What is being controlled
 */
enum class ControlMode{
    SCENE, GUI
};

using Keys = std::vector<bool>;

class Controls {
public:
    ~Controls();

    ControlMode control_mode() {return control_mode_;}
    const Keys& keyboard_keys() {return keyboard_keys_;}
    const MouseEvents& mouse_events() {return mouse_events_;}

    static Controls& GetInstance();

    void OnKeyboardEvent(int action, int key);
    void OnMouseButtonEvent(MouseButtonType type, bool is_pressed,
                            float xpos, float ypos);
    void OnMouseEvent(float xpos, float ypos);

    void SetControlMode(ControlMode control_mode);

    /**
     * Must be called after all EventHandlers were called.
     */
    void Update();

private:
    Controls();

    ControlMode control_mode_;
    Keys keyboard_keys_;
    MouseEvents mouse_events_;
};

}

#endif //PROJECT_CONTROLS_H
