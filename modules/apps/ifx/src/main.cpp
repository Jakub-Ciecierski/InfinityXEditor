#include <factory/scene_factory.h>
#include <rendering/camera/camera.h>
#include <rendering/scene/scene.h>
#include <rendering/renderer.h>
#include <factory/render_object_factory.h>

#include <memory>

int main() {
    ifx::Renderer renderer;
    std::unique_ptr<ifx::Window> window(renderer.window());
    std::unique_ptr<ifx::FBORenderer> fbo_renderer(
                ifx::RenderObjectFactory().CreateFBORenderer(window.get()));
    renderer.SetFBORenderer(std::move(fbo_renderer));

    std::unique_ptr<ifx::Camera> camera(new ifx::Camera(
                                            ObjectID(1),
                                            window->width(), 
                                            window->height()));

    std::unique_ptr<ifx::Scene> scene 
        = ifx::SceneFactory().CreateScene(std::move(camera));
    renderer.SetScene(std::move(scene));

    renderer.startMainLoop();
}
