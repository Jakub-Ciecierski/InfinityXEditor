#ifndef PROJECT_MODEL_FACTORY_H
#define PROJECT_MODEL_FACTORY_H

#include <model/model.h>

namespace ifx {

class ModelFactory {
private:

public:

    ModelFactory();

    ~ModelFactory();

    static Model* LoadAsteroidModel();
    static Model* LoadNanoSuitModel();

    static Model* LoadBicubicBezierSurfaceC0();
    static Model* LoadBicubicBezierPatch();
    static Model* LoadBicubicBezierBowlPatch();
    static Model* LoadBicubicBezierAsymmetricPatch();

    static Model* LoadSquareModel();
    static Model* LoadCubeModel();
    static Model* LoadCubemapModel();
    static Model* LoadLampModel();

    static Model* LoadFloorModel();

};
} // ifx

#endif //PROJECT_MODEL_FACTORY_H
