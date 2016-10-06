#ifndef PROJECT_SCENE_FACTORY_H
#define PROJECT_SCENE_FACTORY_H

#include <rendering/scene/scene.h>

#include <memory>

namespace ifx {

class SceneFactory {
public:

    SceneFactory();
    ~SceneFactory();

    Scene* CreateScene(std::unique<Camera> camera);

    Scene* CreateNanosuitGuy(std::unique<Camera> camera);
    Scene* CreateAsteroidField(std::unique<Camera> camera);
private:
};

}

#endif //PROJECT_SCENE_FACTORY_H
