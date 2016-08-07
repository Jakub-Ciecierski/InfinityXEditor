#ifndef PROJECT_RENDER_OBJECT_FACTORY_H
#define PROJECT_RENDER_OBJECT_FACTORY_H

#include <rendering/render_object.h>

namespace ifx {

class RenderObjectFactory {
public:

    RenderObjectFactory();

    ~RenderObjectFactory();

    RenderObject* loadBicubicBezierSurfaceC0Object();
    RenderObject* loadBicubicBezierPatchObject();
    RenderObject* loadBicubicBezierBowlPatchObject();
    RenderObject* loadBicubicBezierAsymmetricPatchObject();

    RenderObject* loadSquareObject();
    RenderObject* loadCubeObject();
    RenderObject* loadCubemapObject();
    RenderObject* loadLampObject();
    RenderObject* loadnanosuitObject();

private:
    void initModels();

    Model* nanosuitModel;
    Model* squareModel;
    Model* cubeModel;
    Model* cubeMapModel;
    Model* lampModel;

    Model* bicubicBezierSurfaceC0Model;
    Model* bicubicBezierPatchModel;
    Model* bicubicBezierBowlPatchModel;
    Model* bicubicBezierAsymmetricPatchModel;
};
}

#endif //PROJECT_RENDER_OBJECT_FACTORY_H
