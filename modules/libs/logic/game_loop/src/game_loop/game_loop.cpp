#include "game_loop/game_loop.h"

#include <rendering/renderer.h>
#include <vr/simulation.h>

namespace ifx {

GameLoop::GameLoop(std::unique_ptr<Renderer> renderer) :
        renderer_(std::move(renderer)){ }

GameLoop::~GameLoop(){

}

void GameLoop::AddSimulation(std::unique_ptr<Simulation> simulation) {
    simulations_.push_back(std::move(simulation));
}

void GameLoop::Start(){
    while(!renderer_->window()->shouldClose()) {
        renderer_->HandleEvents();
        renderer_->Update();
        renderer_->Render();

        for(auto& simulation : simulations_)
            simulation->Update();
    }

    renderer_->window()->Terminate();
}
}
