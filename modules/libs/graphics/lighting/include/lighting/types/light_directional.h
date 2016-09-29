#ifndef DUCK_LIGHT_DIRECTIONAL_H
#define DUCK_LIGHT_DIRECTIONAL_H

#include "lighting/light_source.h"

namespace ifx {
/*
 * Directional Light has a lookAt position which is used
 * to compute a direction.
 *
 * It binds the position and the direction with the shader.
 */
class LightDirectional : public LightSource {
public:

    LightDirectional();

    LightDirectional(MovableObject *object);

    ~LightDirectional();

    const glm::vec3& lookAt() {return lookAt_;}

    /*
     * Gets direction either from the camera or based on its own
     * position and lookAt
     */
    const glm::vec3 getDirection();

    void setLookAt(const glm::vec3 &lookAt);

    glm::mat4 GetLightSpaceMatrix();
protected:
    virtual void bind(const Program &program, int id = -1) override;

    // Defines the direction of the light.
    // Will be used if light is not set on follow with camera
    glm::vec3 lookAt_;

};
}

#endif //DUCK_LIGHT_DIRECTIONAL_H
