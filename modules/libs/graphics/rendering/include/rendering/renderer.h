#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <rendering/scene/scene.h>
#include <rendering/window.h>
#include <controls/event_handler.h>

#include <memory>

namespace ifx {

class FBORenderer;

enum class RenderingType{
    NORMAL, FBO_TEXTURE
};

class Renderer : public EventHandler{
public:
    Renderer();
    ~Renderer();

    Scene* scene()  {return scene_.get();}
    Window* window()  {return window_.get();}
    RenderingType rendering_type(){return rendering_type_;}

    // Overridden from EventHandler.
    void HandleEvents() override;

    void SetScene(std::unique<Scene> scene);
    void SetRenderingType(RenderingType type);
    void SetFBORenderer(std::unique<FBORenderer> fbo_renderer);

    void startMainLoop();

private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void Update();
    void Render();
    void RenderNormal();
    void RenderFBOTexture();

    std::uqique_ptr<Window> window_;
    std::unique_ptr<Scene> scene_;
    RenderingType rendering_type_;

    std::unique<FBORenderer> fbo_renderer_;
};

}
#endif //PROJECT_RENDERER_H
