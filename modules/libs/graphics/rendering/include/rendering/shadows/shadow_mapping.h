#ifndef PROJECT_SHADOW_MAPPING_H
#define PROJECT_SHADOW_MAPPING_H

#include <memory>

#include <math/math_ifx.h>
#include <shaders/data/shader_data.h>

class Program;

namespace ifx {

class FBO;
class LightDirectional;
class Scene;

/**
 * Creates Shadows in the scene using the Shadow Mapping technique.
 *
 * Only Directional Lights are supported in this Shadow Map version.
 *
 * Creates FBO with Depth Buffer only. Then, renders the scene to texture
 * from the light's perspective, writing only the depth (z).
 *
 * Creates Light Projection Matrix based on light's position and the
 * orthogonal projection.
 */
class ShadowMapping {
public:
    ShadowMapping(Dimensions dimensions,
                  std::shared_ptr<Program> program);
    ~ShadowMapping();

    /**
     * Renders the scene in light's space, writing only depth buffer.
     * Changed Viewport
     */
    void Render(Scene* scene);

private:
    Texture CreateTexture();
    void InitFBO(Texture texture);

    void BindLightMatrix(const Program* program, LightDirectional* light);

    std::unique_ptr<FBO> fbo_;

    std::shared_ptr<Program> program_;

    /**
     * Dimensions of the shadow map. Used to create texture
     */
    Dimensions dimensions_;

    glm::mat4 light_projection_;
    glm::mat4 light_view_;
    glm::mat4 light_MVP_;
};
}

#endif //PROJECT_SHADOW_MAPPING_H
