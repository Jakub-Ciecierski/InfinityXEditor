#ifndef PROJECT_GAME_LOOP_H
#define PROJECT_GAME_LOOP_H

#include <memory>
#include <vector>

namespace ifx {

class Renderer;
class Simulation;

class GameLoop {
public:

    GameLoop(std::unique_ptr<Renderer> renderer);
    ~GameLoop();

    Renderer* renderer(){return renderer_.get();}

    void AddSimulation(std::unique_ptr<Simulation> simulation);
    void Start();

private:
    std::unique_ptr<Renderer> renderer_;
    std::vector<std::unique_ptr<Simulation>> simulations_;

};
}

#endif //PROJECT_GAME_LOOP_H
