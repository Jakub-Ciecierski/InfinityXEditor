#include "factory/model_factory.h"

#include <factory/mesh_factory.h>
#include <model_loader/model_loader.h>
#include <resources/resources.h>
#include <model/model_memory_manager.h>

namespace ifx {

using namespace glm;
using namespace std;

ModelFactory::ModelFactory() {

}

ModelFactory::~ModelFactory() {

}

Model* ModelFactory::LoadNanoSuitModel() {
    ModelMemoryManager& model_manager = ModelMemoryManager::GetInstance();
    Model* cached_model = model_manager.GetNanosuit();
    if(cached_model != nullptr)
        return cached_model;

    Resources &resources = Resources::GetInstance();
    std::string path = resources.GetResourcePath("nanosuit/nanosuit.obj",
                                                 ResourceType::MODEL);

    ModelLoader loader(path);
    Model* model = loader.loadModel();
    model_manager.SetNanosuit(model);

    return model;
}

Model ModelFactory::LoadBicubicBezierSurfaceC0() {
    MeshFactory meshLoader;
    Mesh *mesh1 = meshLoader.LoadBicubicBezierPatch(0, 0, 0.0f, 3, 0);
    Mesh *mesh2 = meshLoader.LoadBicubicBezierPatch(2, 0, 2.0f, 3, 1);
    Mesh *mesh3 = meshLoader.LoadBicubicBezierPatch(4, 0, 1.5f, 3, 2);
    Mesh *mesh4 = meshLoader.LoadBicubicBezierPatch(6, 0, 1.5f, 3, 3);

    Mesh *mesh5 = meshLoader.LoadBicubicBezierPatch(0, 2, 0.2f, 2, 0);
    Mesh *mesh6 = meshLoader.LoadBicubicBezierPatch(2, 2, 0.5f, 2, 1);
    Mesh *mesh7 = meshLoader.LoadBicubicBezierPatch(4, 2, 2.5f, 2, 2);
    Mesh *mesh8 = meshLoader.LoadBicubicBezierPatch(6, 2, -1.5f, 2, 3);

    Mesh *mesh9 = meshLoader.LoadBicubicBezierPatch(0, 4, 0.4f, 1, 0);
    Mesh *mesh10 = meshLoader.LoadBicubicBezierPatch(2, 4, 1.5f, 1, 1);
    Mesh *mesh11 = meshLoader.LoadBicubicBezierPatch(4, 4, -1.5f, 1, 2);
    Mesh *mesh12 = meshLoader.LoadBicubicBezierPatch(6, 4, 1.9f, 1, 3);

    Mesh *mesh13 = meshLoader.LoadBicubicBezierPatch(0, 6, 0.3f, 0, 0);
    Mesh *mesh14 = meshLoader.LoadBicubicBezierPatch(2, 6, 1.5f, 0, 1);
    Mesh *mesh15 = meshLoader.LoadBicubicBezierPatch(4, 6, 1.0f, 0, 2);
    Mesh *mesh16 = meshLoader.LoadBicubicBezierPatch(6, 6, -0.5f, 0, 3);

    std::vector<Mesh *> meshes = {mesh1, mesh2, mesh3, mesh4,
                                  mesh5, mesh6, mesh7, mesh8,
                                  mesh9, mesh10, mesh11, mesh12,
                                  mesh13, mesh14, mesh15, mesh16};

    Model model(meshes);
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(0, 0, 0.0f, 3, 0));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(2, 0, 2.0f, 3, 1));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(4, 0, 1.5f, 3, 2));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(6, 0, 1.5f, 3, 3));

    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(0, 2, 0.2f, 2, 0));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(2, 2, 0.5f, 2, 1));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(4, 2, 2.5f, 2, 2));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(6, 2, -1.5f, 2, 3));

    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(0, 4, 0.4f, 1, 0));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(2, 4, 1.5f, 1, 1));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(4, 4, -1.5f, 1, 2));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(6, 4, 1.9f, 1, 3));

    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(0, 6, 0.3f, 0, 0));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(2, 6, 1.5f, 0, 1));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(4, 6, 1.0f, 0, 2));
    model.addSubMesh(meshLoader.LoadBicubicBezierPolygon(6, 6, -0.5f, 0, 3));

    return model;
}

Model ModelFactory::LoadBicubicBezierPatch() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadBicubicBezierPatch(-1, 1, 1.5f);
    Mesh *meshPolygon1 = meshLoader.LoadBicubicBezierPolygon(-1, 1, 1.5f);

    std::vector<Mesh *> meshes = {mesh};
    Model model(meshes);

    model.addSubMesh(meshPolygon1);

    return model;
}

Model ModelFactory::LoadBicubicBezierBowlPatch() {
    MeshFactory meshLoader;

    Mesh *mesh = meshLoader.LoadBicubicBezierPatch(-1, 1, -1.5f);
    Mesh *meshPolygon1 = meshLoader.LoadBicubicBezierPolygon(-1, 1, -1.5f);
    std::vector<Mesh *> meshes = {mesh};

    Model model(meshes);

    model.addSubMesh(meshPolygon1);

    return model;
}

Model ModelFactory::LoadBicubicBezierAsymmetricPatch() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadBicubicBezierAsymmetricPatch();

    std::vector<Mesh *> meshes = {mesh};

    return Model(meshes);
}

Model ModelFactory::LoadSquareModel() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadPatch();
    std::vector<Mesh *> meshes = {mesh};

    return Model(meshes);
}

Model ModelFactory::LoadCubeModel() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadCube();
    std::vector<Mesh *> meshes = {mesh};

    return Model(meshes);
}

Model ModelFactory::LoadCubemapModel() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadCubemap();
    std::vector<Mesh *> meshes = {mesh};

    return Model(meshes);
}

Model ModelFactory::LoadLampModel() {
    MeshFactory meshLoader;
    Mesh *mesh = meshLoader.LoadLamp();
    std::vector<Mesh *> meshes = {mesh};

    return Model(meshes);
}

} // ifx