#ifndef PROJECT_MESH_FACTORY_H
#define PROJECT_MESH_FACTORY_H

#include <model/mesh.h>

namespace ifx {

class MeshFactory {
private:

public:

    MeshFactory();

    ~MeshFactory();

    static Mesh* LoadBicubicBezierPatch(float startX, float startY,
                                        float depth, int idI = 0, int idJ = 0);
    static Mesh* LoadBicubicBezierPolygon(float startX, float startY,
                                          float depth,
                                          int idI = 0, int idJ = 0);
    static Mesh* LoadBicubicBezierAsymmetricPatch();

    static Mesh* LoadPatch();
    static Mesh* LoadCubemap();
    static Mesh* LoadCube();
    static Mesh* LoadLamp();
};
}

#endif //PROJECT_MESH_FACTORY_H
