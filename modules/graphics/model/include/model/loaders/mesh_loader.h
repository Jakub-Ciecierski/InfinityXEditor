#ifndef DUCK_MESH_LOADER_H
#define DUCK_MESH_LOADER_H

#include "model/mesh.h"

/*
 * Loads specific meshes to the system
 */
class MeshLoader {
private:
    //static void Calculate
public:

    MeshLoader();

    ~MeshLoader();

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


#endif //DUCK_MESH_LOADER_H
