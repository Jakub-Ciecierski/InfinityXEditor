#ifndef DUCK_CONTROLS_H
#define DUCK_CONTROLS_H

#include <rendering/camera/camera.h>

/*
 * Controls the Mouse and Keyboard input
 */
class CameraControls {
private:
    Camera* camera;

    float movementSpeed;
    float rotationSpeed;

    float mouselastX;
    float mouselastY;

    bool mousePressed;

public:

    CameraControls(Camera* camera,
                   float movementSpeed = 0.1f,
                   float rotationSpeed = 0.1f);

    ~CameraControls();

    bool isKeyPress(int key);

    void setMousePress(bool value);
    bool doMovement();

    void setPressedPosition(float x, float y);

    void onMouseAction(float dx, float dy);
    void onKeyboardAction(int action, int key);
};


#endif //DUCK_CONTROLS_H
