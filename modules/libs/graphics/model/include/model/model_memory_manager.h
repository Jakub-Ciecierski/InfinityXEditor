#ifndef PROJECT_MODEL_MEMORY_MANAGER_H
#define PROJECT_MODEL_MEMORY_MANAGER_H

#include <model/model.h>

namespace ifx {

struct Models{
    Model* nanosuit = nullptr;
    Model* asteroid = nullptr;
};

/**
 * Used to cache all loaded models.
 */
class ModelMemoryManager {
public:
    static ModelMemoryManager& GetInstance();
    ~ModelMemoryManager();

    void SetNanosuit(Model* models);
    void SetAsteroid(Model* models);

    Model* GetNanosuit();
    Model* GetAsteroid();

private:
    ModelMemoryManager();

    Models models;
};

}

#endif //PROJECT_MODEL_MEMORY_MANAGER_H
