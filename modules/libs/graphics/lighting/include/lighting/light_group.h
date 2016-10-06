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

    const std::vector<LightPoint *>& light_points(){return light_points_;}
    const std::vector<LightDirectional *>& light_directions(){
        return light_directions_ ;
    }
    const std::vector<LightSpotlight *>& light_spotlights() {
        return light_spotlights_;
    }

    void addLightPoint(std::unique_ptr<LightPoint> light);
    void addLightDirectional(std::unique_ptr<LightDirectional> light);
    void addLightSpotlight(std::unique_ptr<LightSpotlight> light);

    /*
     * Uses all lights. Binds all the data with the shaders
     */
    void use(const Program &program);

    /*
     * Renders all LightSources
     */
    void render(const Program &program);

private:
    std::vector<std::unique_ptr<LightSource>> all_lights_;

    std::vector<LightPoint *> light_points_;
    std::vector<LightDirectional *> light_directions_;
    std::vector<LightSpotlight *> light_spotlights_;

    /*
     * Binds the number of each light type with the shader
     */
    void bindLightCount(const Program &program);

};
}

#endif //DUCK_LIGHT_GROUP_H
