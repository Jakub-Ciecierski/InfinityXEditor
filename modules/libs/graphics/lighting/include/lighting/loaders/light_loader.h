#ifndef DUCK_LIGHT_LOADER_H
#define DUCK_LIGHT_LOADER_H

#include <lighting/types/light_directional.h>
#include <lighting/types/light_point.h>
#include <lighting/types/light_spotlight.h>

/*
 * Loads specific lights to the system
 */
class LightLoader {
private:

public:

    LightLoader();

    ~LightLoader();

    LightPoint*loadPointLight();
    LightDirectional*loadDirLight();
    LightSpotlight* loadSpotlight();
};


#endif //DUCK_LIGHT_LOADER_H
