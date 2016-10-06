#ifndef DUCK_MODEL_H
#define DUCK_MODEL_H

#include "model/mesh.h"
#include <resources/resource.h>

#include <memory>
#include <ostream>

/*
 * Model class is an encapsulation of many meshes take up a single model
 */
class Model : public ifx::Resource {
public:
    /**
     * Creates Model object and adds it to resource cache.
     * If object already exists, loads it from cache.
     */
    static std::shared_ptr<Model> MakeModel(
                std::string filepath, 
                const std::vector<std::unique_ptr<Model>>& meshes);
    ~Model();

    std::vector<Mesh*> getMeshes();
    Mesh* getMesh(int i);

    void draw(const Program& program);
    void drawInstanced(const Program& program, int count);

    std::string toString() const;

private:
    Model(std::string filepath, 
          const std::vector<std::unique_ptr<Model>>& meshes);
    
    //std::vector<Mesh*> meshes;
    std::vector<std::unique_ptr<Model>> meshes;

};

#endif //DUCK_MODEL_H
