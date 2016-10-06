#include <factory/scene_factory.h>
#include <rendering/renderer.h>
#include <factory/render_object_factory.h>
#include <rendering/fbo_rendering/fbo_renderer.h>

#include <memory>

int main() {
    ifx::Renderer renderer;
    ifx::Window* window = renderer.window();
    auto fbo_renderer = ifx::RenderObjectFactory().CreateFBORenderer(window);
    renderer.SetFBORenderer(std::move(fbo_renderer));
    renderer.SetShadowMapping(ifx::RenderObjectFactory().CreateShadowMapping());

    auto camera
            = std::unique_ptr<ifx::Camera>(new ifx::Camera(ObjectID(1),
                                                           window->width(),
                                                           window->height()));
    auto scene = ifx::SceneFactory().CreateScene(std::move(camera));
    renderer.SetScene(std::move(scene));

    renderer.startMainLoop();
}
