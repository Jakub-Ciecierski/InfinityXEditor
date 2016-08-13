#include "factory/scene_factory.h"

#include <factory/lighting_factory.h>
#include <factory/render_object_factory.h>

namespace ifx{

SceneFactory::SceneFactory(){

}

SceneFactory::~SceneFactory(){

}

Scene* SceneFactory::CreateScene(Camera* camera){
    RenderObjectFactory render_object_factory;
    LightingFactory lighting_factory;

    std::vector<RenderObject*> render_objects;
    render_objects.push_back(render_object_factory.loadNanosuitObject());

    LightGroup* group_light = lighting_factory.createGroupLight(camera);

    Scene* scene = new Scene(render_objects,
                             group_light, camera);

    return scene;
}

}