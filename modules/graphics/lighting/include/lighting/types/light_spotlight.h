#ifndef DUCK_LIGHT_SPOTLIGHT_H
#define DUCK_LIGHT_SPOTLIGHT_H

#include <lighting/types/light_directional.h>

/*
 * Represents Flashlight
 * Binds the cutOff angle with the shader
 */
class LightSpotlight : public LightDirectional  {
protected:
    virtual void bind(const Program& program, int id = -1) override;

public:

    LightSpotlight();
    LightSpotlight(RenderObject *object);

    ~LightSpotlight();

};


#endif //DUCK_LIGHT_SPOTLIGHT_H
