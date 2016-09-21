#include "model/model.h"

using namespace std;

Model::Model(const std::vector<Mesh*>& meshes) :
        meshes(meshes){

}

Model::~Model() {
    for(unsigned int i = 0; i < meshes.size(); i++){
        delete meshes[i];
    }
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