#include "model/model_memory_manager.h"

namespace ifx{

ModelMemoryManager::ModelMemoryManager(){

}
ModelMemoryManager::~ModelMemoryManager(){

}

void ModelMemoryManager::SetNanosuit(Model* model){
    if(models.nanosuit != nullptr)
        delete models.nanosuit;
    models.nanosuit = model;
}

void ModelMemoryManager::SetAsteroid(Model* model){
    if(models.asteroid != nullptr)
        delete models.asteroid;
    models.asteroid = model;
}

Model* ModelMemoryManager::GetNanosuit(){
    return models.nanosuit;
}

Model* ModelMemoryManager::GetAsteroid(){
    return models.asteroid;
}

ModelMemoryManager& ModelMemoryManager::GetInstance(){
    static ModelMemoryManager manager;

    return manager;
}

}