#include "factory/scene_factory.h"

#include <factory/lighting_factory.h>
#include <factory/render_object_factory.h>

namespace ifx{

SceneFactory::SceneFactory(){}

SceneFactory::~SceneFactory(){}

std::unique_ptr<Scene> SceneFactory::CreateScene(std::unique_ptr<Camera> camera){
    return CreateEmptyScene(std::move(camera));
}

std::unique_ptr<Scene> SceneFactory::CreateEmptyScene(
        std::unique_ptr<Camera> camera){
    std::unique_ptr<LightGroup> group_light(
            LightingFactory().createGroupLight(camera.get()));

    auto scene = std::unique_ptr<Scene>(new Scene(std::move(group_light),
                                                  std::move(camera)));

    return scene;
}

std::unique_ptr<Scene> SceneFactory::CreateNanosuitGuy(std::unique_ptr<Camera> camera){
    camera->moveTo(glm::vec3(-0.2f, 0.1f, 0.0f));

    std::vector<std::unique_ptr<RenderObject>> render_objects;

    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    RenderObjectFactory().CreateNanosuitObject()));

    std::unique_ptr<LightGroup> group_light(
                LightingFactory().createGroupLight(camera.get()));

    auto scene = std::unique_ptr<Scene>(new Scene(std::move(render_objects),
                                                  std::move(group_light),
                                                  std::move(camera)));

    return scene;
}

std::unique_ptr<Scene> SceneFactory::CreateAsteroidField(std::unique_ptr<Camera> camera){
    camera->moveTo(glm::vec3(-0.2f, 0.1f, 0.0f));

    std::vector<std::unique_ptr<RenderObject>> render_objects;
    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    RenderObjectFactory().CreateAsteroidField()));
    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    RenderObjectFactory().CreateAsteroid()));

    std::unique_ptr<LightGroup> group_light(
                LightingFactory().createGroupLight(camera.get()));

    auto scene = std::unique_ptr<Scene>(new Scene(std::move(render_objects),
                                                  std::move(group_light),
                                                  std::move(camera)));

    return scene;
}

std::unique_ptr<Scene> SceneFactory::CreateShadowMappingTest(std::unique_ptr<Camera> camera){
    camera->moveTo(glm::vec3(-0.2f, 0.1f, 0.0f));

    RenderObjectFactory render_object_factory;
    LightingFactory lighting_factory;

    std::vector<std::unique_ptr<RenderObject>> render_objects;
    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    render_object_factory.CreateNanosuitObject()));
    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    render_object_factory.CreateFloor()));
    render_objects.push_back(
            std::unique_ptr<RenderObject>(
                    render_object_factory.CreateLampObject()));

    render_objects[0]->moveTo(glm::vec3(0.5,0,0.5));

    std::unique_ptr<LightGroup> group_light(
            LightingFactory().createGroupLight(camera.get()));

    auto scene = std::unique_ptr<Scene>(new Scene(std::move(render_objects),
                                                  std::move(group_light),
                                                  std::move(camera)));

    return scene;
}

}