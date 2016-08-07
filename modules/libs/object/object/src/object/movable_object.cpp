#include "object/movable_object.h"

namespace ifx {

MovableObject::MovableObject(ObjectID id, std::string name) :
        Object(id, name) {
    initVectors();
}

MovableObject::~MovableObject() {

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