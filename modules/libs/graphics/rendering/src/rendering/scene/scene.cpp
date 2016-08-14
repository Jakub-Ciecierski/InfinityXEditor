#include "scene/scene.h"

#include <controls/controls.h>

namespace ifx {

Scene::Scene(std::vector<RenderObject *>& render_objects,
             LightGroup* light_group, Camera* camera) :
        render_objects_(render_objects),
        light_group_(light_group),
        camera_(camera) {

}

Scene::~Scene(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        delete render_objects_[i];
    }
    delete light_group_;
    delete camera_;
}

void Scene::HandleEvents() {
    Controls& controls = Controls::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_R]){
        ReloadProgams();
    }
}

void Scene::ReloadProgams(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        render_objects_[i]->getProgram()->Reload();
    }
}

Camera* Scene::SetCamera(Camera* camera){
    Camera* prev_camera = camera_;
    camera_ = camera;

    return prev_camera;
}

void Scene::render(){
    renderObjects();
}

void Scene::update(){
    HandleEvents();
    updateObjects();
    camera_->update();
}

void Scene::renderObjects(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        RenderObject* object = render_objects_[i];
        Program* program = object->getProgram();
        if(program == nullptr)
            continue;

        camera_->use(*program);
        light_group_->use(*program);
        object->render();
    }
}

void Scene::updateObjects(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        render_objects_[i]->update();
    }
}

}