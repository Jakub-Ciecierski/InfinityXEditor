#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include <rendering/render_object.h>
#include <rendering/camera/camera.h>
#include "lighting/light_group.h"

#include <memory>
#include <vector>

namespace ifx {

/**
 * Takes ownership of render_objects, light_group and latest set camera.
 */
class Scene {
public:
    Scene(std::vector<std::unique_ptr<RenderObject>>& render_objects,
          std::unique_ptr<LightGroup> light_group, 
          std::unique_ptr<Camera> camera);

    ~Scene();

    void ReloadProgams();

    void SetCamera(std::unique_ptr<Camera> camera);

    void render();
    void update();

private:
    void render(RenderObject* render_object);
    void updateObjects();

    std::vector<std::unique_ptr<RenderObject>> render_objects_;
    std::unique_ptr<LightGroup> light_group_;
    std::unique_ptr<Camera> camera_;
};

}

#endif //PROJECT_SCENE_H
