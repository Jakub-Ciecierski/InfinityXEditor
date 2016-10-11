#include <factory/scene_factory.h>
#include <rendering/renderer.h>
#include <factory/render_object_factory.h>
#include <rendering/fbo_rendering/fbo_renderer.h>
#include <game_loop/game_loop.h>
#include <memory>

int main() {
    ifx::GameLoop game_loop(
            std::move(ifx::RenderObjectFactory().CreateRenderer()));
    game_loop.Start();
}

