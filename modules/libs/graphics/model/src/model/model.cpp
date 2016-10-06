#include "model/model.h"

#include <resources/resource_memory_cache.h>

using namespace std;

Model::Model(std::string filepath, 
             std::vector<std::unique_ptr<Mesh>> meshes) :
    ifx::Resource(filepath, ifx::ResourceType::MODEL),
    meshes(std::move(meshes)){}

// static
std::shared_ptr<Model> Model::MakeModel(
            std::string filepath, 
            std::vector<std::unique_ptr<Mesh>> meshes){
    std::shared_ptr<Model> model
        = std::static_pointer_cast<Model>(
                    ifx::ResourceMemoryCache::GetInstance().Get(filepath));
    if(!model){
        //model = std::make_shared<Model>(filepath, meshes);
        model = std::shared_ptr<Model>(new Model(filepath, std::move(meshes)));
    }
    ifx::ResourceMemoryCache::GetInstance().Add(model);
    
    return model;
}
    
Model::~Model() {}

std::vector<Mesh*> Model::getMeshes(){
    std::vector<Mesh*> meshes_raw(meshes.size());
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes_raw[i] = meshes[i].get();
    return meshes_raw;
}

Mesh* Model::getMesh(int i){
    return meshes[i].get();
}

void Model::draw(const Program &program) {
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i]->draw(program);
    }
}

void Model::drawInstanced(const Program &program, int count) {
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i]->drawInstanced(program, count);
    }
}

std::string Model::toString() const{
    std::string str = "";
    str += "Mesh count:  " + std::to_string(meshes.size()) + "\n";
    for(unsigned int i = 0; i < meshes.size(); i++){
        str += "Mesh[" + std::to_string(i) + "]" + "\n";
        str += meshes[i]->toString();
    }

    return str;
}