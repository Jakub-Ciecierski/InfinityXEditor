#include <lighting/builders/dirlight_shader_builder.h>
#include "lighting/types/light_directional.h"

using namespace ifx;

LightDirectional::LightDirectional() : LightSource(){

}

LightDirectional::LightDirectional(MovableObject *object) :
        LightSource(object){

}

LightDirectional::~LightDirectional() {

}

const glm::vec3 LightDirectional::getDirection() {
    if(isFollow && movableObject != NULL){
        return movableObject->getDirection();
    }else{
        const glm::vec3& pos = getPosition();
        glm::vec3 dir = lookAt - pos;
        return dir;
    }
}

void LightDirectional::setLookAt(const glm::vec3 &lookAt) {
    this->lookAt = lookAt;
}

void LightDirectional::bind(const Program &program, int id) {
    const glm::vec3& pos = getPosition();
    const glm::vec3 dir = getDirection();

    ifx::DirlightShaderBuilder builder(id);
    builder.build();

    // Light Direction
    GLint lightDirLoc = glGetUniformLocation(program.getID(),
                                             builder.DIRECTION.c_str());
    GLint lightAmbientLoc  = glGetUniformLocation(program.getID(),
                                                  builder.AMBIENT.c_str());
    GLint lightDiffuseLoc  = glGetUniformLocation(program.getID(),
                                                  builder.DIFFUSE.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  builder.SPECULAR.c_str());

    glUniform3f(lightAmbientLoc,
                light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light.specular.x, light.specular.y, light.specular.z);

    glUniform3f(lightDirLoc, dir.x, dir.y, dir.z);
}