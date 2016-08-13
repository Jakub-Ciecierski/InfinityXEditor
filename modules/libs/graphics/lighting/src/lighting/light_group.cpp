#include "lighting/light_group.h"

using namespace ifx;

LightGroup::LightGroup(){

}

LightGroup::~LightGroup(){
    for(unsigned int i = 0; i < allLights.size(); i++){
        delete allLights[i];
    }
}

void LightGroup::bindLightCount(const Program &program) {
    int pointLightCount = lightPointVec.size();
    int dirLightCount = lightDirectionVec.size();
    int spotLightCount = lightSpotlightVec.size();

    GLint pointLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_POINTLIGHT_COUNT.c_str());
    GLint dirLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_DIRLIGHT_COUNT.c_str());
    GLint spotLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_SPOTLIGHT_COUNT.c_str());

    glUniform1i(pointLightCountLoc, pointLightCount);
    glUniform1i(dirLightCountLoc, dirLightCount);
    glUniform1i(spotLightCountLoc, spotLightCount);
}


void LightGroup::addLightPoint(LightPoint* light){
    this->lightPointVec.push_back(light);

    this->allLights.push_back(light);
}

void LightGroup::addLightDirectional(LightDirectional* light){
    this->lightDirectionVec.push_back(light);

    this->allLights.push_back(light);
}

void LightGroup::addLightSpotlight(LightSpotlight* light){
    this->lightSpotlightVec.push_back(light);

    this->allLights.push_back(light);
}

void LightGroup::use(const Program& program){
    bindLightCount(program);

    for(unsigned int i = 0; i < lightPointVec.size(); i++){
        lightPointVec[i]->use(program, i);
    }
    for(unsigned int i = 0; i < lightDirectionVec.size(); i++){
        lightDirectionVec[i]->use(program, i);
    }
    for(unsigned int i = 0; i < lightSpotlightVec.size(); i++){
        lightSpotlightVec[i]->use(program, i);
    }
}

void LightGroup::render(const Program& program){
    for(unsigned int i = 0; i < allLights.size(); i++){
        allLights[i]->render(program);
    }
}
