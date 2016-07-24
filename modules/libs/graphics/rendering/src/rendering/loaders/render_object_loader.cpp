#include <model/loaders/model_demo_loader.h>
#include "rendering/loaders/render_object_loader.h"

RenderObjectLoader::RenderObjectLoader(){
    initModels();
}

RenderObjectLoader::~RenderObjectLoader() {
    delete nanosuitModel;
    delete cubeModel;
    delete cubeMapModel;
    delete lampModel;

    delete bicubicBezierSurfaceC0Model;
    delete bicubicBezierPatchModel;
    delete bicubicBezierBowlPatchModel;
    delete bicubicBezierAsymmetricPatchModel;
}

void RenderObjectLoader::initModels() {
    squareModel = new Model(ModelDemoLoader::LoadSquareModel());
    nanosuitModel = new Model(ModelDemoLoader::LoadNanoSuitModel());
    cubeMapModel = new Model(ModelDemoLoader::LoadCubemapModel());
    cubeModel = new Model(ModelDemoLoader::LoadCubeModel());
    lampModel = new Model(ModelDemoLoader::LoadLampModel());

    bicubicBezierSurfaceC0Model =
            new Model(ModelDemoLoader::LoadBicubicBezierSurfaceC0());
    bicubicBezierPatchModel
            = new Model(ModelDemoLoader::LoadBicubicBezierPatch());
    bicubicBezierBowlPatchModel
            = new Model(ModelDemoLoader::LoadBicubicBezierBowlPatch());
    bicubicBezierAsymmetricPatchModel
            = new Model(ModelDemoLoader::LoadBicubicBezierAsymmetricPatch());
}

RenderObject *RenderObjectLoader::loadBicubicBezierSurfaceC0Object() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierSurfaceC0Model);
    float scaleFactor = 4.0f;

    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 50.0f));
    renderObject->rotateTo(glm::vec3(-90.0f, 0.0f, 0.0f));
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

RenderObject *RenderObjectLoader::loadBicubicBezierPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectLoader::loadBicubicBezierBowlPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierBowlPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(20.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectLoader::loadBicubicBezierAsymmetricPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "BezierPatch",
                               bicubicBezierAsymmetricPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(30.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectLoader::loadSquareObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Square", squareModel);
    float scaleFactor = 4.0f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(1.5f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectLoader::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", cubeModel);

    return renderObject;
}

RenderObject *RenderObjectLoader::loadCubemapObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", cubeMapModel);
    float scaleFactor = 10.0f;
    renderObject->scale(glm::vec3(scaleFactor,
                                  scaleFactor,
                                  scaleFactor));
    return renderObject;
}

RenderObject *RenderObjectLoader::loadLampObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Lamp", lampModel);

    return renderObject;
}

RenderObject* RenderObjectLoader::loadnanosuitObject(){
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "NanoSuit", nanosuitModel);
    float scaleFactor = 0.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}