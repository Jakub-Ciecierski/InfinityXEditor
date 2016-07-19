#include "controls/camera_controls.h"

#include <controls/keys.h>

#include <GLFW/glfw3.h>

CameraControls::CameraControls(Camera* camera,
                               float movementSpeed, float rotationSpeed) :
        camera(camera),
        movementSpeed(movementSpeed), rotationSpeed(rotationSpeed){
    setMousePress(false);
}

CameraControls::~CameraControls() {

}

bool CameraControls::isKeyPress(int key){
    if(key >= KEYS_COUNT || key < 0)
        return false;
    return keys[key];
}

void CameraControls::setMousePress(bool value){
    this->mousePressed = value;
}

bool CameraControls::doMovement() {
    float boost = movementSpeed;
    if(keys[GLFW_KEY_SPACE]){
        boost *= 3.0f;
    }

    if(keys[GLFW_KEY_W])
        camera->moveForward(boost);
    if(keys[GLFW_KEY_S])
        camera->moveBackward(boost);
    if(keys[GLFW_KEY_A])
        camera->moveLeft(boost);
    if(keys[GLFW_KEY_D])
        camera->moveRight(boost);

    if(keys[GLFW_KEY_Q])
        camera->moveUp(boost);
    if(keys[GLFW_KEY_E])
        camera->moveDown(boost);
}

void CameraControls::setPressedPosition(float x, float y){
    mouselastX = x;
    mouselastY = y;
}

void CameraControls::onMouseAction(float xpos, float ypos){
    if(mousePressed) {
        GLfloat xoffset = xpos - mouselastX;
        GLfloat yoffset = mouselastY - ypos;

        mouselastX = xpos;
        mouselastY = ypos;

        camera->rotate(glm::vec3(xoffset * rotationSpeed,
                                 yoffset * rotationSpeed, 0));
    }
}

void CameraControls::onKeyboardAction(int action, int key){
    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            keys[key] = true;
        }else if(action == GLFW_RELEASE){
            keys[key] = false;
        }
    }
}