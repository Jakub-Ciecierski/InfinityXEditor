#include "lighting/light_group.h"

using namespace ifx;

LightGroup::LightGroup(){

}

LightGroup::~LightGroup(){
    for(unsigned int i = 0; i < all_lights_.size(); i++){
        delete all_lights_[i];
    }
}

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


void LightGroup::addLightPoint(LightPoint* light){
    this->light_points_.push_back(light);

    this->all_lights_.push_back(light);
}

void LightGroup::addLightDirectional(LightDirectional* light){
    this->light_directions_.push_back(light);

    this->all_lights_.push_back(light);
}

void LightGroup::addLightSpotlight(LightSpotlight* light){
    this->light_spotlights_.push_back(light);

    this->all_lights_.push_back(light);
}

void LightGroup::use(const Program& program){
    bindLightCount(program);

    for(unsigned int i = 0; i < light_points_.size(); i++){
        light_points_[i]->use(program, i);
    }
    for(unsigned int i = 0; i < light_directions_.size(); i++){
        light_directions_[i]->use(program, i);
    }
    for(unsigned int i = 0; i < light_spotlights_.size(); i++){
        light_spotlights_[i]->use(program, i);
    }
}

void LightGroup::render(const Program& program){
    for(unsigned int i = 0; i < all_lights_.size(); i++){
        all_lights_[i]->render(program);
    }
}
