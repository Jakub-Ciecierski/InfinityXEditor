#include "lighting/light_group.h"

using namespace ifx;

LightGroup::LightGroup(){}

LightGroup::~LightGroup(){}

void LightGroup::bindLightCount(const Program &program) {
    program.use();

    int pointLightCount = light_points_.size();
    int dirLightCount = light_directions_.size();
    int spotLightCount = light_spotlights_.size();

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


void LightGroup::addLightPoint(std::unique_ptr<LightPoint> light){
    this->light_points_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}

void LightGroup::addLightDirectional(std::unique_ptr<LightDirectional> light){
    this->light_directions_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}

void LightGroup::addLightSpotlight(std::unique_ptr<LightSpotlight> light){
    this->light_spotlights_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}

void LightGroup::use(const Program& program){
    bindLightCount(program);

    int i,j,k;
    i = j = k = 0;
    for(auto light : light_points_)
        light->use(program, i++);
    for(auto light : light_directions_)
        light->use(program, j++);
    for(auto light : light_spotlights_)
        light->use(program, k++);
}

void LightGroup::render(const Program& program){
    for(auto& light : all_lights_)
        light->render(program);
}
