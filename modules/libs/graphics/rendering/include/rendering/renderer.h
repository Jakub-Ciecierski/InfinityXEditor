#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <rendering/scene/scene.h>
#include <rendering/window.h>

namespace ifx {

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
    Scene* scene_;

};

}
#endif //PROJECT_RENDERER_H
