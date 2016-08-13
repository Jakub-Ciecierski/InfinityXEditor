#define GLEW_STATIC

#include <rendering/render_object.h>
#include <rendering/window.h>
#include <rendering/camera/camera.h>

#include <lighting/light_source.h>
#include <lighting/light_group.h>

#include <factory/lighting_factory.h>
#include <factory/render_object_factory.h>
#include <factory/program_factory.h>

#include <model/patch/patch.h>

#include <controls/camera_controls.h>

#include <scene/scene.h>

#include <stdexcept>
#include <factory/scene_factory.h>


using namespace std;
using namespace ifx;

// ------------------------------

float lastTick;

int width;
int height;

bool drawPolygon = false;

ifx::Window* window;
CameraControls * controls;
Scene* scene;

// ------------------------------

void initContext();
void initRenderContext();
void initOpenGLContext();
void initCallbacks();

void initScene();

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

    width = 1200;
    height = 800;
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
    Camera* camera = new Camera(ObjectID(1), "camera", &width, &height);
    camera->moveTo(glm::vec3(-1.5f, 0.8f, 0.0f));

    SceneFactory scene_factory;
    scene = scene_factory.CreateScene(camera);

    controls = new CameraControls(camera);

    lastTick = glfwGetTime();
}

void releaseResources(){
    delete window;
    delete scene;
    delete controls;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    controls->onKeyboardAction(action, key);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    controls->onMouseAction(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window,
                           int button, int action, int mods){
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int state_right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    if (state_right == GLFW_PRESS){
        scene->ReloadProgams();
    }

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

}

void update(){
    window->update();
    controls->doMovement();
    scene->update();
}

void render(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->render();
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