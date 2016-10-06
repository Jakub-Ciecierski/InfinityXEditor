#include "factory/scene_factory.h"

#include <factory/lighting_factory.h>
#include <factory/render_object_factory.h>

namespace ifx{

SceneFactory::SceneFactory(){}

SceneFactory::~SceneFactory(){}

Scene* SceneFactory::CreateScene(std::unique<Camera> camera){
    return CreateNanosuitGuy(std::move(camera));
    //return CreateAsteroidField(camera);
}

Scene* SceneFactory::CreateNanosuitGuy(std::unique<Camera> camera){
    camera->moveTo(glm::vec3(-0.2f, 0.1f, 0.0f));

    std::vector<std::unique_ptr<RenderObject>> render_objects;
    render_objects.push_back(RenderObjectFactory().CreateNanosuitObject());

    std::unique_ptr<LightGroup> group_light(
                LightingFactory().createGroupLight(camera));

    Scene* scene = new Scene(std::move(render_objects),
                             std::move(group_light), 
                             std::move(camera));

    return scene;
}

Scene* SceneFactory::CreateAsteroidField(std::unique<Camera> camera){
    camera->moveTo(glm::vec3(-0.2f, 0.1f, 0.0f));

    std::vector<std::unique_ptr<RenderObject>> render_objects;
    render_objects.push_back(render_object_factory.CreateAsteroidField());
    render_objects.push_back(render_object_factory.CreateAsteroid());

    std::unique_ptr<LightGroup> group_light(
                LightingFactory().createGroupLight(camera));

    Scene* scene = new Scene(std::move(render_objects),
                             std::move(group_light), 
                             std::move(camera));

    return scene;
}

}