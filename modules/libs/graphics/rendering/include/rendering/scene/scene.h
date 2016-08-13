#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include <rendering/render_object.h>
#include <rendering/camera/camera.h>
#include "lighting/light_group.h"

#include <vector>

namespace ifx {

/**
 * Takes ownership of render_objects, light_group and latest set camera.
 */
class Scene {
public:
    Scene(std::vector<RenderObject*>& render_objects,
          LightGroup* light_group, Camera* camera);

    ~Scene();

    void ReloadProgams();

    /**
     * Sets new camera, returns pointer to the previous.
     */
    Camera* SetCamera(Camera* camera);

    void render();
    void update();

private:
    void renderObjects();
    void updateObjects();

    std::vector<RenderObject*> render_objects_;
    LightGroup* light_group_;
    Camera* camera_;

};

}

#endif //PROJECT_SCENE_H
