#ifndef PROJECT_SIMULATION_H
#define PROJECT_SIMULATION_H

namespace ifx {

/**
 * Abstract class representing a simple VR Simulation.
 */
class Simulation {
public:

    Simulation();
    virtual ~Simulation();

    virtual void Update() = 0;

};
}

#endif //PROJECT_SIMULATION_H
