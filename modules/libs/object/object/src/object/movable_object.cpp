#include "object/movable_object.h"

namespace ifx {

MovableObject::MovableObject(ObjectID id) :
        Object(id) {
    initVectors();
}

MovableObject::~MovableObject() {

}

void MovableObject::update(){
    ModelMatrix = glm::mat4(1.0f);

    glm::mat4 Translate = translate(glm::mat4(1.0f), position);

    glm::mat4 RotateX = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 RotateY = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 RotateZ = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), scaleFactor);

    glm::mat4 Rotate =  RotateZ * RotateY * RotateX;

    ModelMatrix = Translate * Rotate * Scale;
}

void MovableObject::moveTo(const glm::vec3 &position) {
    this->position = position;
}

void MovableObject::move(const glm::vec3 &position) {
    this->position += position;
}

void MovableObject::rotateTo(const glm::vec3 &rotate) {
    this->rotation = rotate;
}

void MovableObject::rotate(const glm::vec3 &rotate) {
    this->rotation += rotate;
}

void MovableObject::scale(const glm::vec3 &scale) {
    this->scaleFactor = scale;
}

const glm::vec3& MovableObject::getPosition() {
    return this->position;
}

const glm::vec3& MovableObject::getDirection(){
    return this->direction;
}


void MovableObject::initVectors(){
    scaleFactor = glm::vec3(1.0f, 1.0f, 1.0f);
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
}


} // ifx