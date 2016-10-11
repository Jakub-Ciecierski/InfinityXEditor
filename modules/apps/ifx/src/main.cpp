#include <factory/scene_factory.h>
#include <factory/render_object_factory.h>
#include <game_loop/game_loop.h>
#include <object/render_object.h>
#include <rendering/renderer.h>
#include <rendering/fbo_rendering/fbo_renderer.h>
#include <vr/spring1D/spring_simulation_1D.h>

#include <spring_gui.h>

#include <memory>

void InitScene(ifx::GameLoop* game_loop);
void InitSpringGUI(ifx::GameLoop* game_loop,
                   ifx::SpringSimulation1D* simulation);
void InitSpringSimulation(ifx::GameLoop* game_loop,
                          RenderObject* spring_object,
                          RenderObject* mass_object);

void InitScene(ifx::GameLoop* game_loop){
    ifx::Scene* scene = game_loop->renderer()->scene();
    scene->camera()->moveTo(glm::vec3(-2.84f, -0.57f, -2.84f));
    scene->camera()->rotateTo(glm::vec3(40.96, 4.81, 40.96));

    auto spring_object = ifx::RenderObjectFactory().CreateSpring();
    auto mass_object = ifx::RenderObjectFactory().CreateMassSpring();
    InitSpringSimulation(game_loop, spring_object.get(), mass_object.get());

    scene->AddRenderObject(std::move(ifx::RenderObjectFactory().CreateRoom()));
    scene->AddRenderObject(std::move(mass_object));
    scene->AddRenderObject(std::move(spring_object));
}

void InitSpringGUI(ifx::GameLoop* game_loop,
                   ifx::SpringSimulation1D* simulation){
    auto gui = std::unique_ptr<ifx::GUI>(
            new SpringGUI(
                    game_loop->renderer()->window()->getHandle(),
                    simulation));
    game_loop->renderer()->SetGUI(std::move(gui));
}

void InitSpringSimulation(ifx::GameLoop* game_loop,
                          RenderObject* spring_object,
                          RenderObject* mass_object){
    ifx::Spring1DParameters params;
    params.initial_mass_object.position = 0.0f;
    params.initial_mass_object.velocity = 0.1f;
    params.initial_mass_object.mass = 10.0f;
    params.initial_mass_object.render_object = mass_object;

    params.initial_spring.damping_factor = 0.2f;
    params.initial_spring.spring_factor = 0.1f;
    params.initial_spring.amplitude = 1.00f;
    params.initial_spring.frequency = 0.1f;
    params.initial_spring.phase_shift = 0.1f;
    params.initial_spring.render_object = spring_object;

    params.time_delta = 0.005;

    auto simulation = std::unique_ptr<ifx::SpringSimulation1D>(
            new ifx::SpringSimulation1D(params));
    InitSpringGUI(game_loop, simulation.get());
    game_loop->AddSimulation(std::move(simulation));
}

int main() {
    ifx::GameLoop game_loop(
            std::move(ifx::RenderObjectFactory().CreateRenderer()));

    InitScene(&game_loop);

    game_loop.Start();
}

