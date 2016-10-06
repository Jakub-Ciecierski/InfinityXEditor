#include "lighting/light_group.h"

using namespace ifx;

LightGroup::LightGroup(){}

LightGroup::~LightGroup(){}

void LightGroup::bindLightCount(const Program &program) {
    program.use();

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


void LightGroup::addLightPoint(std::unique<LightPoint> light){
    this->lightPointVec.push_back(light.get());

    this->allLights.push_back(std::move(light));
}

void LightGroup::addLightDirectional(std::unique<LightDirectional> light){
    this->lightDirectionVec.push_back(light.get());

    this->allLights.push_back(std::move(light));
}

void LightGroup::addLightSpotlight(std::unique<LightSpotlight> light){
    this->lightSpotlightVec.push_back(light.get());

    this->allLights.push_back(std::move(light));
}

void LightGroup::use(const Program& program){
    bindLightCount(program);

    for(auto light : lightPointVec)
        light->use(program, i);
    for(auto light : lightDirectionVec)
        light->use(program, i);
    for(auto light : lightSpotlightVec)
        light->use(program, i);
}

void LightGroup::render(const Program& program){
    for(auto light& : allLights)
        light->render(program);
}
