#include <lighting/light_group.h>
#include "factory/lighting_factory.h"

#include <memory>

namespace ifx {

LightingFactory::LightingFactory() {

}

LightingFactory::~LightingFactory() {

}

LightPoint *LightingFactory::loadPointLight() {
    LightPoint *lightSource = new LightPoint();

    Light light;
    /*
    light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular= glm::vec3(1.0f, 1.0f, 1.0f);
    */
    light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.0032;

    lightSource->setLight(light);
    return lightSource;
}

LightDirectional *LightingFactory::loadDirLight() {
    LightDirectional *lightSource = new LightDirectional();

    Light light;
    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    lightSource->setLight(light);

    lightSource->setPosition(glm::vec3(0.5f, 0.7f, 0.0f));
    lightSource->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    lightSource->setFollow(false);

    return lightSource;
}

LightSpotlight *LightingFactory::loadSpotlight() {
    LightSpotlight *lightSource = new LightSpotlight();

    Light light;
    //light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    //light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.ambient = glm::vec3(0.9f, 0.9f, 0.9f);
    light.diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.032;

    light.cutOff = 22.5f;
    light.outerCutOff = 27.5f;

    lightSource->setLight(light);

    lightSource->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    return lightSource;
}

LightGroup* LightingFactory::createGroupLight(Camera* camera){
    LightGroup* light_group = new LightGroup();

    std::unique_ptr<LightDirectional> light(loadDirLight());
    light_group->addLightDirectional(std::move(light));

    return light_group;
}

}