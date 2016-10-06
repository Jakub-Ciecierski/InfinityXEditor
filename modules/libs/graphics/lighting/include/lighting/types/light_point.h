#ifndef DUCK_LIGHT_GLOBAL_H
#define DUCK_LIGHT_GLOBAL_H

#include "lighting/light_source.h"

namespace ifx {
/*
 * Global Light simply binds the position with the shader.
 */
class LightPoint : public LightSource {
protected:
    virtual void bind(const Program &program, int id = -1) override;

public:

    LightPoint();

    LightPoint(MovableObject *renderObject);

    ~LightPoint();

};
}

#endif //DUCK_LIGHT_GLOBAL_H
