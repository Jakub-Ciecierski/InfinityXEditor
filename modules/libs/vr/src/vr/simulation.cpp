#include "vr/simulation.h"

namespace ifx {

Simulation::Simulation() : running_(true){}
Simulation::~Simulation(){}

bool Simulation::IsRunning(){
    return running_;
}
bool Simulation::SetRunning(bool value){
    running_ = value;
}

}