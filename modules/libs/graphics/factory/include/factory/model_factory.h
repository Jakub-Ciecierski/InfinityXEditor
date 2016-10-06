#ifndef PROJECT_MODEL_FACTORY_H
#define PROJECT_MODEL_FACTORY_H

#include <model/model.h>

namespace ifx {

class ModelFactory {
public:

    ModelFactory();
    ~ModelFactory();

    static std::shared_ptr<Model> LoadAsteroidModel();
    static std::shared_ptr<Model> LoadNanoSuitModel();

    static std::shared_ptr<Model> LoadBicubicBezierSurfaceC0();
    static std::shared_ptr<Model> LoadBicubicBezierPatch();
    static std::shared_ptr<Model> LoadBicubicBezierBowlPatch();
    static std::shared_ptr<Model> LoadBicubicBezierAsymmetricPatch();

    static std::shared_ptr<Model> LoadSquareModel();
    static std::shared_ptr<Model> LoadCubeModel();
    static std::shared_ptr<Model> LoadCubemapModel();
    static std::shared_ptr<Model> LoadLampModel();

private:
    static std::shared_ptr<Model> LoadModel(std::string path);

};
} // ifx

#endif //PROJECT_MODEL_FACTORY_H
