#include "vr/spring1D/spring_simulation_1D.h"

#include <object/render_object.h>
#include "GLFW/glfw3.h"

namespace ifx{

SpringSimulation1D::SpringSimulation1D(const Parameters& params) :
        mass_object_(params.initial_mass_object),
        spring_(params.initial_spring),
        time_delta_(params.time_delta),
        time_delta_sqr_(time_delta_*time_delta_),
        current_update_time_(-1),
        last_update_time_(-1){

}

SpringSimulation1D::~SpringSimulation1D(){

}

void SpringSimulation1D::Update(){
    if(!SatisfiesTimeDelta())
        return;

    mass_object_.position = ComputeNextPosition();

    UpdateObjects();
}

double SpringSimulation1D::ComputeNextPosition(){

    double mul
            = 1.0 / (1.0 + ((time_delta_ * spring_.damping_factor)
                            / 2 * mass_object_.mass));
    double a
            = (((time_delta_ * spring_.damping_factor) /
                    2 * mass_object_.mass) - 1)
              * mass_object_.previous_position;
    double b
            = (spring_.damping_factor
              * (ComputeEquilibriumShift() - mass_object_.position)
              * time_delta_sqr_) / mass_object_.mass;
    double c =
            (ComputeExternalFieldForce() * time_delta_sqr_) / mass_object_.mass;
    double d = 2 * mass_object_.position;

    return mul * (a+b+c+d);

}

double SpringSimulation1D::ComputeEquilibriumShift(){
    return ComputeShiftFunction();
}

double SpringSimulation1D::ComputeExternalFieldForce(){
    return ComputeShiftFunction();
}

double SpringSimulation1D::ComputeShiftFunction(){
    if(spring_.shift_function == ShiftFunction::CONSTANT)
        return ComputeConstantFunction();
    else if(spring_.shift_function == ShiftFunction::JUMPING)
        return ComputeJumpingFunction();
    else if(spring_.shift_function == ShiftFunction::JUMPING_CONST)
        return ComputeJumpingConstantFunction();
    else if(spring_.shift_function == ShiftFunction::SINUSOIDAL)
        return ComputeSinusoidalFunction();

    return -99999.9;
}

double SpringSimulation1D::ComputeConstantFunction(){
    return spring_.amplitude;
}

double SpringSimulation1D::ComputeJumpingFunction(){
    if(current_update_time_ < 0)
        return 0;
    else
        return spring_.amplitude;
}

double SpringSimulation1D::ComputeJumpingConstantFunction(){
    return 0.0f;
}

double SpringSimulation1D::ComputeSinusoidalFunction(){
    return spring_.amplitude
           * sin(spring_.frequency*current_update_time_ + spring_.phase_shift);
}

bool SpringSimulation1D::SatisfiesTimeDelta(){
    current_update_time_= glfwGetTime();
    double time_delta = current_update_time_ - last_update_time_;
    last_update_time_ = current_update_time_;
    return time_delta >= time_delta_;
}

void SpringSimulation1D::UpdateObjects(){
    glm::vec3 position = mass_object_.render_object->getPosition();
    position.y = mass_object_.position;

    mass_object_.render_object->moveTo(position);
}

}