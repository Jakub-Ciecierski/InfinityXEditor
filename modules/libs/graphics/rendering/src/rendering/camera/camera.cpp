#include "rendering/camera/camera.h"

#include "shaders/data/shader_data.h"

namespace ifx {

Camera::Camera(ObjectID id, std::string name,
               int *width, int *height,
               float FOV, float near, float far) :
        MovableObject(id, name),
        width(width), height(height),
        FOV(FOV), near(near), far(far) {
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    position = glm::vec3(1.0f, 1.0f, 1.0f);
    update();
}

Camera::~Camera() {

}

void Camera::rotate(const glm::vec3 &rotation) {
    this->rotation += rotation;
    clampRotation();
}

void Camera::rotateTo(const glm::vec3 &rotation) {
    this->rotation = rotation;
    clampRotation();
}

void Camera::update() {
    ProjectionMatrix = glm::perspective(FOV,
                                        (float) (*width) / (float) (*height),
                                        near, far);

    direction.x = cos(glm::radians(rotation.x))
                  * cos(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.y));
    direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

    direction = glm::normalize(direction);
    right = glm::normalize(glm::cross(direction, this->WorldUp));
    up = glm::normalize(glm::cross(right, direction));

    ViewMatrix = glm::lookAt(position, position + direction, up);
}

void Camera::moveForward(float speedBoost) {
    position += direction * speedBoost;
}

void Camera::moveBackward(float speedBoost) {
    position -= direction * speedBoost;
}

void Camera::moveLeft(float speedBoost) {
    position -= right * speedBoost;
}

void Camera::moveRight(float speedBoost) {
    position += right * speedBoost;
}

void Camera::moveUp(float speedBoost) {
    position += up * speedBoost;
}

void Camera::moveDown(float speedBoost) {
    position -= up * speedBoost;
}

void Camera::use(const Program &program) {
    program.use();

    // View Matrix
    GLint viewLoc = glGetUniformLocation(program.getID(),
                                         VIEW_MATRIX_NAME.c_str());
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));

    // Projection Matrix
    GLint projLoc = glGetUniformLocation(program.getID(),
                                         PROJECTION_MATRIX_NAME.c_str());
    glUniformMatrix4fv(projLoc, 1, GL_FALSE,
                       glm::value_ptr(getProjectionMatrix()));

    // View Position
    GLint viewPosLoc = glGetUniformLocation(program.getID(),
                                            VIEW_POSITION_NAME.c_str());
    glUniform3f(viewPosLoc, position.x, position.y, position.z);
}

const glm::mat4 &Camera::getViewMatrix() {
    return this->ViewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() {
    return this->ProjectionMatrix;
}

void Camera::clampRotation() {
    if (rotation.y < -89) {
        rotation.y = -89;
    }
    if (rotation.y > 89) {
        rotation.y = 89;
    }
}

}