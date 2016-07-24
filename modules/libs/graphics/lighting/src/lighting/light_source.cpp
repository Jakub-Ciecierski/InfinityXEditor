#include <glm/detail/type_vec.hpp>
#include <lighting/light_source.h>

using namespace ifx;

LightSource::LightSource(){
    followedRenderObject = NULL;
    followedCamera = NULL;

    setFollow(true);
}

LightSource::LightSource(RenderObject *renderObject) :
        followedRenderObject(renderObject){
    followedCamera = NULL;
    setFollow(true);
}

LightSource::~LightSource() {

}

void LightSource::setRenderObject(RenderObject* object){
    this->followedRenderObject = object;
    this->followedCamera = NULL;
}

void LightSource::setCamera(Camera *camera) {
    this->followedCamera = camera;
    this->followedRenderObject = NULL;
}


void LightSource::setFollow(bool value) {
    isFollow = value;
}

void LightSource::setPosition(const glm::vec3 &position) {
    this->position = position;
}

void LightSource::setLight(const Light& light){
    this->light = light;
}

const glm::vec3 &LightSource::getPosition() {
    if(isFollow && followedRenderObject != NULL){
        return followedRenderObject->getPosition();
    }else if(isFollow && followedCamera != NULL){
        return followedCamera->getPosition();
    }else{
        return this->position;
    }
}

void LightSource::use(const Program& program, int id) {
    program.use();

    bind(program, id);
}

void LightSource::render(const Program &program) {
    if(followedRenderObject == NULL) return;

    followedRenderObject->render(program);
}
