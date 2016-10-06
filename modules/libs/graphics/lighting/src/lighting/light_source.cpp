#include <lighting/light_source.h>

namespace ifx {

LightSource::LightSource() {
    setFollow(true);
}

LightSource::LightSource(MovableObject *renderObject) :
        movableObject(renderObject) {
    setFollow(true);
}

LightSource::~LightSource() {}

void LightSource::setMovableObject(MovableObject* movableObject) {
    this->movableObject = movableObject;
}

void LightSource::setFollow(bool value) {
    isFollow = value;
}

void LightSource::setPosition(const glm::vec3 &position) {
    this->position = position;
}

void LightSource::setLight(const Light &light) {
    this->light = light;
}

const glm::vec3 &LightSource::getPosition() {
    if (isFollow && movableObject != NULL) {
        return movableObject->getPosition();
    }  else {
        return this->position;
    }
}

void LightSource::use(const Program &program, int id) {
    program.use();

    bind(program, id);
}

void LightSource::render(const Program &program) {
    if (movableObject == NULL) return;
}

} // ifx