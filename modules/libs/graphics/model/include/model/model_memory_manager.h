#ifndef PROJECT_MODEL_MEMORY_MANAGER_H
#define PROJECT_MODEL_MEMORY_MANAGER_H

#include <model/model.h>

namespace ifx {

struct Models{
    Model* nanosuit = nullptr;
};

/**
 * Used to cache all loaded models.
 */
class ModelMemoryManager {
public:
    static ModelMemoryManager& GetInstance();
    ~ModelMemoryManager();

    void SetNanosuit(Model* models);
    Model* GetNanosuit();

private:
    ModelMemoryManager();

    Models models;
};

}

#endif //PROJECT_MODEL_MEMORY_MANAGER_H
