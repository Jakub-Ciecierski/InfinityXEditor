#define GLEW_STATIC

#include <rendering/render_object.h>
#include <rendering/window.h>
#include <rendering/camera/camera.h>

#include <shaders/loaders/program_loader.h>
#include <shaders/program.h>

#include <lighting/light_source.h>
#include <lighting/light_group.h>

#include <factory/lighting_factory.h>
#include <factory/render_object_factory.h>
#include <factory/program_factory.h>

#include <model/patch/patch.h>

#include <controls/camera_controls.h>

#include <math/math_ifx.h>

#include <iostream>
#include <stdexcept>
#include <factory/program_factory.h>


using namespace std;
using namespace ifx;

// ------------------------------

float lastTick;

int width;
int height;

bool drawPolygon = false;

ifx::Window* window;

Camera* camera;
CameraControls * controls;

RenderObjectFactory* renderObjectLoader;
RenderObject* squareObjectPointLight;
RenderObject* squareObjectPointLight2;
RenderObject* squareObjectDirLight;

RenderObject* boxObject;

RenderObject* patchObject;
std::vector<RenderObject*> patchesObjects;
RenderObject* bezierSurfaceC0Object;
RenderObject* bezierPatchObject;
RenderObject* bezierBowlPatchObject;
RenderObject* bezierAsymmetricPatchObject;

LightingFactory lightLoader;
LightGroup lightGroup;
LightPoint* lightPoint1;
LightPoint* lightPoint2;
LightDirectional* lightDirectional;
LightSpotlight* lightSpotlight;

ProgramFactory programFactory;

Program* programBumpMap;
Program* programLight;
Program* programLamp;
Program* programTess;
Program* programTessBezier;
Program* programTessLOD;
Program* programTessBezierPolygon;
// ------------------------------

void initContext();
void initRenderContext();
void initOpenGLContext();
void initCallbacks();

void initScene();
void initExampleMeshes();
void initShaders();

void releaseResources();

void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window,
                           int button, int action, int mods);
void mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mainLoop();

void update();
void render();

// ------------------------------

int main() {
    initContext();
    initScene();

    mainLoop();

    releaseResources();

    return 0;
}
void initContext(){
    initRenderContext();

    width = 800;
    height = 600;
    window = new ifx::Window(width, height, "Tessellation");

    initOpenGLContext();
    initCallbacks();
}

void initRenderContext(){
    glfwInit();
    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void initOpenGLContext(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        throw new std::invalid_argument("Failed to initialize GLEW");
    }
}

void initCallbacks(){
    glfwSetKeyCallback(window->getHandle(), key_callback);
    glfwSetCursorPosCallback(window->getHandle(), mouse_callback);
    glfwSetMouseButtonCallback(window->getHandle(), mouse_button_callback);
    glfwSetScrollCallback(window->getHandle(), mousescroll_callback);
}


void initScene(){
    camera = new Camera(ObjectID(1), "camera", &width, &height);
    camera->moveTo(glm::vec3(-1.5f, 0.8f, 0.0f));

    controls = new CameraControls(camera);

    initShaders();
    initExampleMeshes();

    lastTick = glfwGetTime();
}

void initExampleMeshes(){
    renderObjectLoader = new RenderObjectFactory();
    boxObject = renderObjectLoader->loadCubeObject();

    squareObjectPointLight = renderObjectLoader->loadLampObject();
    squareObjectPointLight2 = renderObjectLoader->loadLampObject();
    squareObjectDirLight = renderObjectLoader->loadLampObject();

    bezierSurfaceC0Object
            = renderObjectLoader->loadBicubicBezierSurfaceC0Object();
    patchObject
            = renderObjectLoader->loadSquareObject();
    bezierPatchObject
            = renderObjectLoader->loadBicubicBezierPatchObject();
    bezierBowlPatchObject
            = renderObjectLoader->loadBicubicBezierBowlPatchObject();
    bezierAsymmetricPatchObject
            = renderObjectLoader->loadBicubicBezierAsymmetricPatchObject();

    patchesObjects.push_back(bezierSurfaceC0Object);
    patchesObjects.push_back(patchObject);
    patchesObjects.push_back(bezierPatchObject);
    patchesObjects.push_back(bezierBowlPatchObject);
    patchesObjects.push_back(bezierAsymmetricPatchObject);

    // ------

    lightPoint1 = lightLoader.loadPointLight();
    lightPoint2 = lightLoader.loadPointLight();
    lightDirectional = lightLoader.loadDirLight();
    lightSpotlight = lightLoader.loadSpotlight();

    lightPoint1->setMovableObject(squareObjectPointLight);
    lightPoint2->setMovableObject(squareObjectPointLight2);
    lightDirectional->setMovableObject(squareObjectDirLight);
    lightSpotlight->setMovableObject(camera);
    // -------

    //lightGroup.addLightDirectional(lightDirectional);
    lightGroup.addLightSpotlight(lightSpotlight);
    lightGroup.addLightPoint(lightPoint1);
    lightGroup.addLightPoint(lightPoint2);

    // -------
    squareObjectDirLight->moveTo(glm::vec3(30.0f, 5.0f, 15.0f));
    squareObjectPointLight->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    squareObjectPointLight2->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    squareObjectPointLight2->moveTo(glm::vec3(10.0f, 15.0f, 35.0f));
}

void initShaders(){
    programBumpMap = programFactory.loadBumpMappingProgram();
    programLight = programFactory.loadAllLightProgram();
    programLamp = programFactory.loadLampProgram();
    programTess = programFactory.loadTessellationProgram();
    programTessBezier = programFactory.loadTessellationBicubicBezierProgram();
    programTessLOD = programFactory.loadTessellationLODProgram();
    programTessBezierPolygon
            = programFactory.loadTessellationBicubicBezierPolygonProgram();
}

void releaseResources(){
    delete window;

    delete programBumpMap;
    delete programLight;
    delete programLamp;
    delete programTess;
    delete programTessBezier;
    delete programTessLOD;
    delete programTessBezierPolygon;

    delete boxObject;
    delete bezierSurfaceC0Object;
    delete renderObjectLoader;
    delete squareObjectPointLight;
    delete patchObject;
    delete bezierPatchObject;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    controls->onKeyboardAction(action, key);
    if(controls->isKeyPress(GLFW_KEY_X)){
        drawPolygon = !drawPolygon;
    }
    if(controls->isKeyPress(GLFW_KEY_Z)){
        for(unsigned int i = 0; i < patchesObjects.size(); i++){
            const std::vector<Mesh*>& meshes =
                    patchesObjects[i]->getModel()->getMeshes();
            for(unsigned int i = 0; i < meshes.size(); i++){
                Mesh* mesh = meshes[i];
                GLenum polygonMode = mesh->getPolygonMode();
                if(polygonMode == GL_LINE){
                    mesh->setPolygonMode(GL_FILL);
                }if(polygonMode == GL_FILL){
                    mesh->setPolygonMode(GL_LINE);
                }
            }
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    controls->onMouseAction(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window,
                           int button, int action, int mods){
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(state == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        controls->setMousePress(true);
        controls->setPressedPosition(xpos, ypos);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }else if(state == GLFW_RELEASE){
        controls->setMousePress(false);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    Patch* patch = static_cast<Patch*>(patchObject->getModel()->getMesh(0));
    Patch* bezierPatch
            = static_cast<Patch*>(bezierPatchObject->getModel()->getMesh(0));
    Patch* bezierBowlPatch
            = static_cast<Patch*>
            (bezierBowlPatchObject->getModel()->getMesh(0));
    Patch* bezierAsymPatch
            = static_cast<Patch*>
            (bezierAsymmetricPatchObject->getModel()->getMesh(0));

    if(controls->isKeyPress(GLFW_KEY_LEFT_SHIFT)){
        patch->addToTessLevelOuter(yoffset);
        bezierPatch->addToTessLevelOuter(yoffset);
        bezierBowlPatch->addToTessLevelOuter(yoffset);
        bezierAsymPatch->addToTessLevelOuter(yoffset);

        const std::vector<Mesh*>& meshes
                = bezierSurfaceC0Object->getModel()->getMeshes();
        for(unsigned int i = 0; i < meshes.size(); i++){
            Patch* patch = static_cast<Patch*>(meshes[i]);
            patch->addToTessLevelOuter(yoffset);
        }
    }else{
        patch->addToTessLevelInner(yoffset);
        bezierPatch->addToTessLevelInner(yoffset);
        bezierBowlPatch->addToTessLevelInner(yoffset);
        bezierAsymPatch->addToTessLevelInner(yoffset);

        const std::vector<Mesh*>& meshes
                = bezierSurfaceC0Object->getModel()->getMeshes();
        for(unsigned int i = 0; i < meshes.size(); i++){
            Patch* patch = static_cast<Patch*>(meshes[i]);
            patch->addToTessLevelInner(yoffset);
        }
    };
}

void update(){
    window->update();

    controls->doMovement();
    camera->update();

    boxObject->update();

    squareObjectDirLight->update();

    patchObject->update();
    bezierSurfaceC0Object->update();
    bezierPatchObject->update();
    bezierBowlPatchObject->update();

    // MOVE LIGHT 1

    static float a = 0;
    const float da = 0.05f;
    static float curr_da = da;
    if(a > 35) curr_da = -da;
    if(a < 0) curr_da = da;

    squareObjectPointLight->moveTo(glm::vec3(a, 0.0f, 10.0f));
    squareObjectPointLight->update();
    a += curr_da;

    // MOVE LIGHT 2
    static float rot = 0;
    float radius = 10.0f;
    squareObjectPointLight2->moveTo(glm::vec3(25 + cos(rot)*radius,
                                              15.0f,
                                              45.0f + sin(rot)*radius));
    squareObjectPointLight2->update();

    rot+=0.01f;
    if(rot > 360) rot = 0;

}

void render(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Program* program = programLight;

    camera->use(*program);
    lightGroup.use(*program);
    boxObject->render(*program);

    camera->use(*programTess);
    lightGroup.use(*programTess);
    patchObject->render(*programTess);

    camera->use(*programTessBezier);
    lightGroup.use(*programTessBezier);
    bezierPatchObject->render(*programTessBezier);
    bezierBowlPatchObject->render(*programTessBezier);

    camera->use(*programTessLOD);
    lightGroup.use(*programTessLOD);
    bezierSurfaceC0Object->render(*programTessLOD);

    if(drawPolygon){
        camera->use(*programTessBezierPolygon);
        lightGroup.use(*programTessBezierPolygon);
        bezierSurfaceC0Object->render(*programTessBezierPolygon,
                                      RenderModels::SUB_MODEL);
        bezierPatchObject->render(*programTessBezierPolygon,
                                  RenderModels::SUB_MODEL);
        bezierBowlPatchObject->render(*programTessBezierPolygon,
                                      RenderModels::SUB_MODEL);
    }

    // Draw Lamp
    camera->use(*programLamp);
    squareObjectPointLight->render(*programLamp);
    squareObjectPointLight2->render(*programLamp);
}

void mainLoop(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!window->shouldClose())
    {
        update();
        render();

        glfwSwapBuffers(window->getHandle());
    }
    glfwTerminate();
}