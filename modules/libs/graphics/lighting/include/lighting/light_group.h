#ifndef DUCK_LIGHT_GROUP_H
#define DUCK_LIGHT_GROUP_H

#include <lighting/types/light_point.h>
#include <lighting/types/light_spotlight.h>

#include <vector>

#include <memory>

namespace ifx {
/*
 * LightGroup combines all lights in the scene and renders them using
 * one shader.
 *
 * Moreover LightGroup takes ownership of all Lights.
 * If a LightSource is removed, then LightGroup also losed owner ship of it
 */
class LightGroup {
public:

    LightGroup();
    ~LightGroup();

    void addLightPoint(std::unique<LightPoint> light);
    void addLightDirectional(std::unique<LightDirectional> light);
    void addLightSpotlight(std::unique<LightSpotlight> light);

    /*
     * Uses all lights. Binds all the data with the shaders
     */
    void use(const Program &program);

    /*
     * Renders all LightSources
     */
    void render(const Program &program);

private:
    std::vector<std::unique<LightSource>> allLights;

    std::vector<LightPoint *> lightPointVec;
    std::vector<LightDirectional *> lightDirectionVec;
    std::vector<LightSpotlight *> lightSpotlightVec;

    /*
     * Binds the number of each light type with the shader
     */
    void bindLightCount(const Program &program);

};
}

#endif //DUCK_LIGHT_GROUP_H
