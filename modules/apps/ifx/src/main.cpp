#include <factory/scene_factory.h>
#include <rendering/camera/camera.h>
#include <rendering/scene/scene.h>
#include <rendering/renderer.h>

int main() {
    ifx::Renderer renderer;
    ifx::Window* window = renderer.window();
    ifx::Camera* camera = new ifx::Camera(ObjectID(1), "camera",
                                          window->width(), window->height());
    camera->moveTo(glm::vec3(-1.5f, 0.8f, 0.0f));

    ifx::Scene* scene = ifx::SceneFactory().CreateScene(camera);
    renderer.SetScene(scene);

    renderer.startMainLoop();
}
