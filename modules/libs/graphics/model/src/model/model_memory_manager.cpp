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

Model* ModelMemoryManager::GetNanosuit(){
    return models.nanosuit;
}

ModelMemoryManager& ModelMemoryManager::GetInstance(){
    static ModelMemoryManager manager;

    return manager;
}

}