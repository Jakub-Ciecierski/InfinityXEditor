#include <factory/scene_factory.h>
#include <rendering/camera/camera.h>
#include <rendering/scene/scene.h>
#include <rendering/renderer.h>
#include <factory/render_object_factory.h>

int main() {
    ifx::Renderer renderer;
    ifx::Window* window = renderer.window();
    ifx::FBORenderer* fbo_renderer = ifx::RenderObjectFactory()
            .CreateFBORenderer(window);
    renderer.SetFBORenderer(fbo_renderer);
    renderer.SetShadowMapping(ifx::RenderObjectFactory().CreateShadowMapping());

    ifx::Camera* camera
            = new ifx::Camera(ObjectID(1), window->width(), window->height());

    ifx::Scene* scene = ifx::SceneFactory().CreateScene(camera);
    renderer.SetScene(scene);

    renderer.startMainLoop();
}
