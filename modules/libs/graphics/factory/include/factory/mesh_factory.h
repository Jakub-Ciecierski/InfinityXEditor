#ifndef PROJECT_MESH_FACTORY_H
#define PROJECT_MESH_FACTORY_H

#include <model/mesh.h>

#include <memory>

namespace ifx {

class MeshFactory {
private:

public:

    MeshFactory();

    ~MeshFactory();

    static std::unique_ptr<Mesh> LoadBicubicBezierPatch(float startX,
                                                        float startY,
                                                        float depth,
                                                        int idI = 0,
                                                        int idJ = 0);
    static std::unique_ptr<Mesh> LoadBicubicBezierPolygon(float startX,
                                                          float startY,
                                                          float depth,
                                                          int idI = 0,
                                                          int idJ = 0);
    static std::unique_ptr<Mesh> LoadBicubicBezierAsymmetricPatch();

    static std::unique_ptr<Mesh> LoadPatch();
    static std::unique_ptr<Mesh> LoadCubemap();
    static std::unique_ptr<Mesh> LoadCube();
    static std::unique_ptr<Mesh> LoadRoom();
    static std::unique_ptr<Mesh> LoadFloor();
    static std::unique_ptr<Mesh> LoadLamp();
};
}

#endif //PROJECT_MESH_FACTORY_H
