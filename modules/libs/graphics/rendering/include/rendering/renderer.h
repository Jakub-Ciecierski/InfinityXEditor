#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <rendering/scene/scene.h>
#include <rendering/window.h>
#include <controls/event_handler.h>

namespace ifx {

class FBORenderer;

enum class RenderingType{
    NORMAL, FBO_TEXTURE
};

class Renderer : public EventHandler{
public:
    Renderer();
    ~Renderer();

    Scene* scene()  {return scene_;}
    Window* window()  {return window_;}
    RenderingType rendering_type(){return rendering_type_;}

    // Overridden from EventHandler.
    void HandleEvents() override;

    /**
     * Sets scene and returns previous.
     */
    Scene* SetScene(Scene* scene);
    void SetRenderingType(RenderingType type);
    void SetFBORenderer(FBORenderer* fbo_renderer);

    void startMainLoop();

private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void Update();
    void Render();
    void RenderNormal();
    void RenderFBOTexture();

    Window* window_;
    Scene* scene_;
    RenderingType rendering_type_;

    FBORenderer* fbo_renderer_;
};

}
#endif //PROJECT_RENDERER_H
