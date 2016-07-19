#ifndef DUCK_LIGHT_GROUP_H
#define DUCK_LIGHT_GROUP_H

#include <lighting/types/light_point.h>
#include <lighting/types/light_spotlight.h>

/*
 * LightGroup combines all lights in the scene and renders them using
 * one shader.
 *
 * Moreover LightGroup takes ownership of all Lights.
 * If a LightSource is removed, then LightGroup also losed owner ship of it
 */
class LightGroup {
private:
    std::vector<LightSource*> allLights;

    std::vector<LightPoint*> lightPointVec;
    std::vector<LightDirectional*> lightDirectionVec;
    std::vector<LightSpotlight*> lightSpotlightVec;

    /*
     * Binds the number of each light type with the shader
     */
    void bindLightCount(const Program& program);

public:

    LightGroup();

    ~LightGroup();

    void addLightPoint(LightPoint* light);
    void addLightDirectional(LightDirectional* light);
    void addLightSpotlight(LightSpotlight* light);

    /*
     * Uses all lights. Binds all the data with the shaders
     */
    void use(const Program& program);

    /*
     * Renders all LightSources
     */
    void render(const Program& program);
};


#endif //DUCK_LIGHT_GROUP_H
