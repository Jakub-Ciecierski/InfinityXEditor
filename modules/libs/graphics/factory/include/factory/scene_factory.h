#ifndef PROJECT_SCENE_FACTORY_H
#define PROJECT_SCENE_FACTORY_H

#include <rendering/scene/scene.h>

namespace ifx {

class SceneFactory {
public:

    SceneFactory();

    ~SceneFactory();

    Scene* CreateScene(Camera* camera);

    Scene* CreateNanosuitGuy(Camera* camera);
    Scene* CreateAsteroidField(Camera* camera);
private:
};

}

#endif //PROJECT_SCENE_FACTORY_H
