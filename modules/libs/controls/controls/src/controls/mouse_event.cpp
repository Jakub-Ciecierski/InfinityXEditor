#include "controls/mouse_event.h"

namespace ifx {

MouseEvent::MouseEvent(MouseButtonType type) :
        type_(type),
        is_pressed_(false),
        x_(0), y_(0) {

}

MouseEvent::~MouseEvent(){

}

}