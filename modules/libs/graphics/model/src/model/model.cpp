#include "model/model.h"

using namespace std;

Model::Model(const std::vector<Mesh*>& meshes) :
        meshes(meshes){

}

Model::Model(const Model& other){
    //meshes = other.meshes;
    //subMeshes = other.subMeshes;

    for(unsigned int i = 0; i < other.meshes.size(); i++){
        Mesh* mesh = other.meshes[i];
        //Mesh* newMesh = new Mesh(*mesh);
        meshes.push_back(mesh);
    }
    for(unsigned int i = 0; i < other.subMeshes.size(); i++){
        Mesh* mesh = other.subMeshes[i];
        subMeshes.push_back(mesh);
    }
}

Model::~Model() {
    /*
    for(unsigned int i = 0; i < meshes.size(); i++){
        delete meshes[i];
    }
    for(unsigned int i = 0; i < subMeshes.size(); i++){
        delete subMeshes[i];
    }*/
}

void Model::addSubMesh(Mesh* mesh){
    subMeshes.push_back(mesh);
}

const std::vector<Mesh*>& Model::getMeshes(){
    return this->meshes;
}

Mesh* Model::getMesh(int i){
    return meshes[i];
}

void Model::draw(const Program &program) {
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i]->draw(program);
    }
}

void Model::drawSubMeshes(const Program &program) {
    for(unsigned int i = 0; i < subMeshes.size(); i++){
        subMeshes[i]->draw(program);
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