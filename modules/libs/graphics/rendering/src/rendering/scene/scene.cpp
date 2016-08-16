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

void Scene::ReloadProgams(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        const std::vector<Program*>& programs =
                render_objects_[i]->programs();
        for(unsigned int j = 0; j < programs.size(); j++){
            programs[j]->Reload();
        }
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
    updateObjects();
    camera_->update();
}

void Scene::renderObjects(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        RenderObject* object = render_objects_[i];
        const std::vector<Program*>& programs = object->programs();
        for(unsigned int j = 0; j < programs.size(); j++){
            camera_->use(*programs[j]);
            light_group_->use(*programs[j]);
            object->render(*programs[j]);
        }
    }
}

void Scene::updateObjects(){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        render_objects_[i]->update();
    }
}

}