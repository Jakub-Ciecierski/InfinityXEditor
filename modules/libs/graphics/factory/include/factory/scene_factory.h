#ifndef PROJECT_SCENE_FACTORY_H
#define PROJECT_SCENE_FACTORY_H

#include <rendering/scene/scene.h>

#include <memory>

namespace ifx {

class SceneFactory {
public:

    SceneFactory();
    ~SceneFactory();

    std::unique_ptr<Scene> CreateScene(std::unique_ptr<Camera> camera);

    std::unique_ptr<Scene> CreateEmptyScene(std::unique_ptr<Camera> camera);
    std::unique_ptr<Scene> CreateNanosuitGuy(std::unique_ptr<Camera> camera);
    std::unique_ptr<Scene> CreateAsteroidField(std::unique_ptr<Camera> camera);

    std::unique_ptr<Scene> CreateShadowMappingTest(std::unique_ptr<Camera> camera);
private:
};

}

#endif //PROJECT_SCENE_FACTORY_H
