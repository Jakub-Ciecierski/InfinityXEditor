#include "factory/model_factory.h"

#include <factory/mesh_factory.h>
#include <model_loader/model_loader.h>
#include <model/model_memory_manager.h>
#include <resources/resources.h>

#include <memory>

namespace ifx {

using namespace glm;
using namespace std;

ModelFactory::ModelFactory() {

}

ModelFactory::~ModelFactory() {

}

std::shared_ptr<Model> ModelFactory::LoadAsteroidModel() {
    std::string path
        = Resources::GetInstance().GetResourcePath("asteroid/rock.obj",
                                                   ResourceType::MODEL);
    return LoadModel(path);
}

std::shared_ptr<Model> ModelFactory::LoadNanoSuitModel() {
    std::string path
        = Resources::GetInstance().GetResourcePath("nanosuit/nanosuit.obj",
                                                   ResourceType::MODEL);
    return LoadModel(path);
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierSurfaceC0() {
    MeshFactory meshLoader;
/*
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

    std::vector<std::unique_ptr<Mesh>> meshes{
            std::unique_ptr<Mesh>(mesh1),
            std::unique_ptr<Mesh>(mesh2),
            std::unique_ptr<Mesh>(mesh3),
            std::unique_ptr<Mesh>(mesh4),
            std::unique_ptr<Mesh>(mesh5),
            std::unique_ptr<Mesh>(mesh6),
            std::unique_ptr<Mesh>(mesh7),
            std::unique_ptr<Mesh>(mesh8),
            std::unique_ptr<Mesh>(mesh9),
            std::unique_ptr<Mesh>(mesh10),
            std::unique_ptr<Mesh>(mesh11),
            std::unique_ptr<Mesh>(mesh12),
            std::unique_ptr<Mesh>(mesh13),
            std::unique_ptr<Mesh>(mesh14),
            std::unique_ptr<Mesh>(mesh15),
            std::unique_ptr<Mesh>(mesh16)
    };
    return Model::MakeModel("BicubicBezierSurfaceC0", std::move(meshes));
    */

    return nullptr;
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierPatch() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadBicubicBezierPatch(-1, 1, 1.5f)));

    return Model::MakeModel("BicubicBezierPatch", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierBowlPatch() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadBicubicBezierPatch(-1, 1, 1.5f)));

    return Model::MakeModel("BicubicBezierBowlPatch", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierAsymmetricPatch() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadBicubicBezierAsymmetricPatch()));

    return Model::MakeModel("BicubicBezierAsymmetricPatch", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadSquareModel() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadPatch()));

    return Model::MakeModel("SquareModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCubeModel() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadCube()));

    return Model::MakeModel("CubeModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadRoomModel() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadRoom()));

    return Model::MakeModel("RoomModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCubemapModel() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadCubemap()));

    return Model::MakeModel("CubemapModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadLampModel() {
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadLamp()));

    return Model::MakeModel("LampModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadModel(std::string path) {
    return ModelLoader(path).loadModel();
}

std::shared_ptr<Model> ModelFactory::LoadFloorModel(){
    MeshFactory meshLoader;

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(meshLoader.LoadFloor()));

    return Model::MakeModel("Floor", std::move(meshes));
}

} // ifx