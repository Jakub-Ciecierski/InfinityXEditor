#ifndef PROJECT_LIGHTING_FACTORY_H
#define PROJECT_LIGHTING_FACTORY_H

#include <lighting/types/light_directional.h>
#include <lighting/types/light_point.h>
#include <lighting/types/light_spotlight.h>
#include <rendering/camera/camera.h>

namespace ifx {
/*
 * Loads specific lights to the system
 */
class LightingFactory {
private:

public:

    LightingFactory();

    ~LightingFactory();

    LightPoint *loadPointLight();

    LightDirectional *loadDirLight();

    LightSpotlight *loadSpotlight();

    LightGroup* createGroupLight(Camera* camera);

};
}

#endif //PROJECT_LIGHTING_FACTORY_H
