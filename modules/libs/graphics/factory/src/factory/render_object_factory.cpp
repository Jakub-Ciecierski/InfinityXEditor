#include "factory/render_object_factory.h"

#include <factory/model_factory.h>
#include <math/math_ifx.h>

namespace ifx{


RenderObjectFactory::RenderObjectFactory(){
    initModels();
}

RenderObjectFactory::~RenderObjectFactory() {
    delete nanosuitModel;
    delete cubeModel;
    delete cubeMapModel;
    delete lampModel;

    delete bicubicBezierSurfaceC0Model;
    delete bicubicBezierPatchModel;
    delete bicubicBezierBowlPatchModel;
    delete bicubicBezierAsymmetricPatchModel;
}

void RenderObjectFactory::initModels() {
    squareModel = new Model(ModelFactory::LoadSquareModel());
    nanosuitModel = new Model(ModelFactory::LoadNanoSuitModel());
    cubeMapModel = new Model(ModelFactory::LoadCubemapModel());
    cubeModel = new Model(ModelFactory::LoadCubeModel());
    lampModel = new Model(ModelFactory::LoadLampModel());

    bicubicBezierSurfaceC0Model =
            new Model(ModelFactory::LoadBicubicBezierSurfaceC0());
    bicubicBezierPatchModel
            = new Model(ModelFactory::LoadBicubicBezierPatch());
    bicubicBezierBowlPatchModel
            = new Model(ModelFactory::LoadBicubicBezierBowlPatch());
    bicubicBezierAsymmetricPatchModel
            = new Model(ModelFactory::LoadBicubicBezierAsymmetricPatch());
}

RenderObject *RenderObjectFactory::loadBicubicBezierSurfaceC0Object() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierSurfaceC0Model);
    float scaleFactor = 4.0f;

    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 50.0f));
    renderObject->rotateTo(glm::vec3(-90.0f, 0.0f, 0.0f));
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierBowlPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierBowlPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(20.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierAsymmetricPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierAsymmetricPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(30.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadSquareObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Square", squareModel);
    float scaleFactor = 4.0f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(1.5f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", cubeModel);

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubemapObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", cubeMapModel);
    float scaleFactor = 10.0f;
    renderObject->scale(glm::vec3(scaleFactor,
                                  scaleFactor,
                                  scaleFactor));
    return renderObject;
}

RenderObject *RenderObjectFactory::loadLampObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Lamp", lampModel);

    return renderObject;
}

RenderObject* RenderObjectFactory::loadnanosuitObject(){
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "NanoSuit", nanosuitModel);
    float scaleFactor = 0.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

}