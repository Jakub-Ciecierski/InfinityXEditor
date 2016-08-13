#ifndef DUCK_CAMERA_H
#define DUCK_CAMERA_H

#include <shaders/program.h>
#include <object/movable_object.h>
#include <math/math_ifx.h>
namespace ifx {

/*
 * Camera represents the Projection and View Matrices.
 * Uses Eulor angles (lookAt) FPS style.
 */
class Camera : public ifx::MovableObject {
public:
    Camera(ObjectID id, std::string name,
           int *width, int *height,
           float FOV = 45.0f,
           float near = 0.01f, float far = 100.0f);

    ~Camera();

    /**
     * Override from MovableObject.
     */
    void rotate(const glm::vec3 &rotation) override;

    void rotateTo(const glm::vec3 &rotation) override;

    /**
     * Override from Object.
     */
    virtual void update() override;

    void moveForward(float speedBoost);

    void moveBackward(float speedBoost);

    void moveLeft(float speedBoost);

    void moveRight(float speedBoost);

    void moveUp(float speedBoost);

    void moveDown(float speedBoost);

    void use(const Program &program);

    const glm::mat4 &getViewMatrix();

    const glm::mat4 &getProjectionMatrix();

private:
    void clampRotation();

    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 WorldUp;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    int *width;
    int *height;

    float FOV;

    float near;
    float far;

};
}

#endif //DUCK_CAMERA_H

