#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <rendering/camera/controls/camera_controls.h>
#include <rendering/window.h>
#include <rendering/scene/scene.h>

namespace ifx {

void key_callback(GLFWwindow *window, int key,
                  int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window,
                    double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window,
                           int button, int action, int mods);
void mousescroll_callback(GLFWwindow *window,
                          double xoffset, double yoffset);

class Renderer {
public:
    Renderer();
    ~Renderer();

    Scene* scene()  {return scene_;}
    Window* window()  {return window_;}

    /**
     * Sets scene and returns previous.
     */
    Scene* SetScene(Scene* scene);

    void startMainLoop();

private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void Update();
    void Render();

    Window* window_;
    CameraControls* controls_;
    Scene* scene_;

};

}
#endif //PROJECT_RENDERER_H
