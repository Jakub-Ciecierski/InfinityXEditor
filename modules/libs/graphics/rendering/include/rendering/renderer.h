#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <memory>

#include <controls/event_handler.h>
#include <rendering/scene/scene.h>
#include <rendering/window.h>
#include <rendering/shadows/shadow_mapping.h>

namespace ifx {

class FBORenderer;

/**
 * Render to window directly or to texture.
 * Rendering to texture allow for post-processing.
 */
enum class RenderingType{
    NORMAL, FBO_TEXTURE
};

/**
 * Type of shadows to render.
 */
enum class ShadowsType{
    NONE, SHADOW_MAPPING
};

/**
 * Takes ownership over ShadowMapping
 */
class Renderer : public EventHandler{
public:
    Renderer();
    ~Renderer();

    Scene* scene()  {return scene_;}
    Window* window()  {return window_;}
    RenderingType rendering_type(){return rendering_type_;}
    ShadowsType shadow_type(){return shadow_type_;};

    // Overridden from EventHandler.
    void HandleEvents() override;

    /**
     * Sets scene and returns previous.
     */
    Scene* SetScene(Scene* scene);
    void SetRenderingType(RenderingType type);
    void SetShadowsType(ShadowsType type);

    void SetFBORenderer(FBORenderer* fbo_renderer);
    void SetShadowMapping(ShadowMapping* shadow_mapping);

    void startMainLoop();

private:
    void initGLFWRenderContext();
    void initOpenGLContext();
    void initGLFWCallbacks();

    void Update();
    void Render();
    void RenderNormal();
    void RenderNormalShadowMapping();
    void RenderFBOTexture();

    Window* window_;
    Scene* scene_;
    RenderingType rendering_type_;
    ShadowsType shadow_type_;

    FBORenderer* fbo_renderer_;

    std::unique_ptr<ShadowMapping> shadow_mapping_;
};

}
#endif //PROJECT_RENDERER_H
