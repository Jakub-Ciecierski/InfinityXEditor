#ifndef DUCK_MODEL_H
#define DUCK_MODEL_H

#include "model/mesh.h"
#include <ostream>

/*
 * Model class is an encapsulation of many meshes take up a single model
 */
class Model {
public:

    Model(const std::vector<Mesh*>& meshes);
    ~Model();

    Model(const Model& other) = delete;
    Model& operator=(const Model& other) = delete;

    const std::vector<Mesh*>& getMeshes();
    Mesh* getMesh(int i);

    void draw(const Program& program);
    void drawInstanced(const Program& program, int count);

    std::string toString() const;

private:
    std::vector<Mesh*> meshes;

};

#endif //DUCK_MODEL_H
