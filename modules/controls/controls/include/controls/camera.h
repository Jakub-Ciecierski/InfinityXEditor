#ifndef DUCK_CAMERA_H
#define DUCK_CAMERA_H

#include <rendering/shaders/program.h>

#include <glm/gtc/matrix_transform.hpp>


/*
 * Camera represents the Projection and View Matrices.
 * Uses Eulor angles (lookAt) FPS style.
 */
class Camera {
private:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 WorldUp;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    int* width;
    int* height;

    float FOV;

    float near;
    float far;

public:

    Camera(int* width, int* height,
           float FOV = 45.0f,
           float near = 0.01f, float far = 100.0f);

    ~Camera();
    void clampRotation();

    void moveTo(const glm::vec3& position);
    void moveForward(float speedBoost);
    void moveBackward(float speedBoost);
    void moveLeft(float speedBoost);
    void moveRight(float speedBoost);
    void moveUp(float speedBoost);
    void moveDown(float speedBoost);

    void rotate(const glm::vec3& rotation);
    void rotateTo(const glm::vec3& rotation);

    void update();

    void use(const Program &program);

    const glm::vec3& getPosition();
    const glm::vec3& getDirection();

    const glm::mat4& getViewMatrix();
    const glm::mat4& getProjectionMatrix();
};


#endif //DUCK_CAMERA_H

