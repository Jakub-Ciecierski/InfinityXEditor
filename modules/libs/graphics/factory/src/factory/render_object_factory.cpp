#include "factory/render_object_factory.h"

#include <math/math_ifx.h>
#include <factory/model_factory.h>
#include <factory/program_factory.h>
#include <rendering/fbo_rendering/fbo_renderer.h>
#include <rendering/instanced_render_object.h>

#include <GLFW/glfw3.h>

namespace ifx{


RenderObjectFactory::RenderObjectFactory(){
}

RenderObjectFactory::~RenderObjectFactory() {

}

FBORenderer* RenderObjectFactory::CreateFBORenderer(Window* window){
    FBORenderer* fbo_renderer = new FBORenderer(window);
    fbo_renderer->SetProgram(ProgramFactory().LoadFBOProgram());

    return fbo_renderer;
}

RenderObject* RenderObjectFactory::CreateAsteroidField(){
    ProgramFactory program_factory;
    Program* program = program_factory.LoadInstancedProgram();

    Model* model = ModelFactory::LoadAsteroidModel();

    InstancedData instanced_data;
    instanced_data.data_count = 10000;
    instanced_data.model_matrices.resize(instanced_data.data_count);

    srand(glfwGetTime()); // initialize random seed
    GLfloat radius = 2.5;
    GLfloat offset = 1.0f;
    for(GLuint i = 0; i < instanced_data.data_count; i++) {
        glm::mat4 model;
        // 1. Translation: displace along circle with 'radius' in range [-offset, offset]
        GLfloat angle = (GLfloat)i / (GLfloat)instanced_data.data_count * 360.0f;
        GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat x = sin(angle) * radius + displacement;
        displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat y = displacement * 0.4f; // y value has smaller displacement
        displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));
        // 2. Scale: Scale between 0.05 and 0.25f
        GLfloat scale = (rand() % 5) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));
        // 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
        GLfloat rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        // 4. Now add to list of matrices
        instanced_data.model_matrices[i] = model;
    }

    InstancedRenderObject* instanced_render_object
            = new InstancedRenderObject(ObjectID(0), model, instanced_data);
    instanced_render_object->addProgram(program);

    return instanced_render_object;
}

RenderObject* RenderObjectFactory::CreateAsteroid(){
    ProgramFactory program_factory;
    Program* program = program_factory.loadBumpMappingProgram();

    Model* model = ModelFactory::LoadAsteroidModel();

    RenderObject* renderObject
            = new RenderObject(ObjectID(0), model);

    renderObject->addProgram(program);

    float scaleFactor = 0.05f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

RenderObject* RenderObjectFactory::CreateNanosuitObject(){
    ProgramFactory program_factory;

    Program* nano_program = program_factory.loadBumpMappingProgram();
    Program* normal_vision_program = program_factory.LoadNormalVisionProgram();

    Model* nanosuitModel = ModelFactory::LoadNanoSuitModel();

    RenderObject* renderObject
            = new RenderObject(ObjectID(0), nanosuitModel);

    renderObject->addProgram(nano_program);
    renderObject->addProgram(normal_vision_program);

    float scaleFactor = 0.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

/*
RenderObject *RenderObjectFactory::loadBicubicBezierSurfaceC0Object() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierSurfaceC0Model);
    float scaleFactor = 4.0f;

    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 50.0f));
    renderObject->rotateTo(glm::vec3(-90.0f, 0.0f, 0.0f));
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierBowlPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierBowlPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(20.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierAsymmetricPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierAsymmetricPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(30.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadSquareObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), squareModel);
    float scaleFactor = 4.0f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(1.5f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), cubeModel);

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubemapObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), cubeMapModel);
    float scaleFactor = 10.0f;
    renderObject->scale(glm::vec3(scaleFactor,
                                  scaleFactor,
                                  scaleFactor));
    return renderObject;
}

RenderObject *RenderObjectFactory::loadLampObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), lampModel);

    return renderObject;
}

RenderObject* RenderObjectFactory::loadNanosuitObject(){
    ProgramFactory program_factory;

    Program* nano_program = program_factory.loadBumpMappingProgram();
    Program* normal_vision_program = program_factory.LoadNormalVisionProgram();

    Model* nanosuitModel = ModelFactory::LoadNanoSuitModel();

    RenderObject* renderObject
            = new RenderObject(ObjectID(0), nanosuitModel);

    renderObject->addProgram(nano_program);
    renderObject->addProgram(normal_vision_program);

    float scaleFactor = 0.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}*/

}