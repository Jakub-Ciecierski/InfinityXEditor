#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include <rendering/render_object.h>
#include <controls/camera.h>
#include "lighting/light_group.h"

#include <vector>

namespace ifx {

class Scene {
private:
    std::vector<RenderObject*> render_objects_;
    LightGroup*
    Camera* camera_;
public:

    Scene();

    ~Scene();

};

}

#endif //PROJECT_SCENE_H
