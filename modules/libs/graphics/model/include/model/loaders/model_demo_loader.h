#ifndef DUCK_MODEL_DEMO_LOADER_H
#define DUCK_MODEL_DEMO_LOADER_H

#include <model/model.h>

/*
 * Uses ModelLoader to load demo models
 */
class ModelDemoLoader {
private:

public:

    ModelDemoLoader();

    ~ModelDemoLoader();

    static Model LoadNanoSuitModel();

    static Model LoadBicubicBezierSurfaceC0();
    static Model LoadBicubicBezierPatch();
    static Model LoadBicubicBezierBowlPatch();
    static Model LoadBicubicBezierAsymmetricPatch();

    static Model LoadSquareModel();
    static Model LoadCubeModel();
    static Model LoadCubemapModel();
    static Model LoadLampModel();
};


#endif //DUCK_MODEL_DEMO_LOADER_H
