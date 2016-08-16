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
    Model(const Model& other);

    ~Model();

    void addSubMesh(Mesh* mesh);

    const std::vector<Mesh*>& getMeshes();
    Mesh* getMesh(int i);

    void draw(const Program& program);
    void drawSubMeshes(const Program &program);

    std::string toString() const;

private:
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> subMeshes;

};

#endif //DUCK_MODEL_H
