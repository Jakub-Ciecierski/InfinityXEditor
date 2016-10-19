#include "vr/spring1D/spring_simulation_1D.h"

#include <object/render_object.h>
#include "GLFW/glfw3.h"

namespace ifx{

SpringSimulation1D::SpringSimulation1D(const Spring1DParameters& params) :
        mass_object_(params.initial_mass_object),
        spring_(params.initial_spring),
        time_delta_(params.time_delta),
        time_delta_sqr_(time_delta_*time_delta_),
        current_update_time_(0),
        last_update_time_(0),
        total_time_s_(0){
    mass_object_.previous_position
            = mass_object_.position - time_delta_*mass_object_.velocity;
}

SpringSimulation1D::~SpringSimulation1D(){}

void SpringSimulation1D::Reset(const Spring1DParameters& params){
    mass_object_ = params.initial_mass_object;
    spring_ = params.initial_spring;
    time_delta_ = params.time_delta;
    time_delta_sqr_ = time_delta_*time_delta_;
    current_update_time_ = glfwGetTime();
    last_update_time_ = glfwGetTime();
    total_time_s_ = 0;

    mass_object_.previous_position
            = mass_object_.position - time_delta_*mass_object_.velocity;

    ClearCache();
}

void SpringSimulation1D::Update(){
    if(!SatisfiesTimeDelta())
        return;

    double next_position = ComputeNextPosition();

    UpdateCache(mass_object_.previous_position,
                mass_object_.position,
                next_position);

    double pos_tmp = mass_object_.position;
    mass_object_.position = next_position;
    mass_object_.previous_position = pos_tmp;

    UpdateObjects();
}

double SpringSimulation1D::ComputeNextPosition(){
    double mul
            = 1.0 / (1.0 + ((time_delta_ * spring_.damping_factor)
                            / 2 * mass_object_.mass));
    double a
            = (((time_delta_ * spring_.damping_factor) /
                    (2 * mass_object_.mass)) - 1)
              * mass_object_.previous_position;
    double b
            = (spring_.spring_factor
              * (ComputeEquilibriumShift() - mass_object_.position)
              * time_delta_sqr_) / mass_object_.mass;
    double c =
            (ComputeExternalFieldForce() * time_delta_sqr_) / mass_object_.mass;
    double d = 2 * mass_object_.position;

    return mul * (a+b+c+d);

}

double SpringSimulation1D::ComputeEquilibriumShift(){
    return ComputeShiftFunction(spring_.equilibrium_function);
}

double SpringSimulation1D::ComputeExternalFieldForce(){
    return ComputeShiftFunction(spring_.external_field_function);
}

double SpringSimulation1D::ComputeShiftFunction(ShiftFunction shift_function){
    if(shift_function == ShiftFunction::CONSTANT)
        return ComputeConstantFunction();
    else if(shift_function == ShiftFunction::JUMPING)
        return ComputeJumpingFunction();
    else if(shift_function == ShiftFunction::JUMPING_CONST)
        return ComputeJumpingConstantFunction();
    else if(shift_function == ShiftFunction::SINUSOIDAL)
        return ComputeSinusoidalFunction();

    return -99999.9;
}

double SpringSimulation1D::ComputeConstantFunction(){
    return spring_.amplitude;
}

double SpringSimulation1D::ComputeJumpingFunction(){
    float x = spring_.amplitude
        * sin(spring_.frequency*current_update_time_ + spring_.phase_shift);
    if (x < -1) return -1;
    else if (x==0) return 0;
    else return 1;
}

double SpringSimulation1D::ComputeJumpingConstantFunction(){
    if(current_update_time_ < 0)
        return 0;
    else
        return spring_.amplitude;
}

double SpringSimulation1D::ComputeSinusoidalFunction(){
    return spring_.amplitude
           * sin(spring_.frequency*current_update_time_ + spring_.phase_shift);
}

bool SpringSimulation1D::SatisfiesTimeDelta(){
    current_update_time_ = glfwGetTime();
    if(!running_){
        last_update_time_ = current_update_time_;
        return false;
    }
    double time_delta = current_update_time_ - last_update_time_;
    total_time_s_ += time_delta;

    bool value = time_delta >= time_delta_;
    if(value)
        last_update_time_ = current_update_time_;

    return value;
}

void SpringSimulation1D::UpdateCache(double prev_position,
                                     double current_position,
                                     double next_position){
    double velocity = (next_position - prev_position) / (2 * time_delta_);
    double acceleration = (next_position - 2*current_position + prev_position)
                          / (time_delta_sqr_);

    double spring_force = spring_.spring_factor
                          * (ComputeEquilibriumShift() - current_position);
    double damping_force = -(spring_.damping_factor * velocity);
    double external_force = ComputeExternalFieldForce();
    double equilibrium_function = ComputeEquilibriumShift();

    spring_cache_.positions_.push_back(current_position);
    spring_cache_.velocities_.push_back(velocity);
    spring_cache_.accelerations_.push_back(acceleration);
    spring_cache_.spring_force.push_back(spring_force);
    spring_cache_.damping_force.push_back(damping_force);
    spring_cache_.external_force.push_back(external_force);
    spring_cache_.equilibrium_function.push_back(equilibrium_function);
}

void SpringSimulation1D::ClearCache(){
    spring_cache_.positions_.clear();
    spring_cache_.velocities_.clear();
    spring_cache_.accelerations_.clear();
    spring_cache_.spring_force.clear();
    spring_cache_.damping_force.clear();
    spring_cache_.external_force.clear();
    spring_cache_.equilibrium_function.clear();
}

void SpringSimulation1D::UpdateObjects(){
    glm::vec3 position = mass_object_.render_object->getPosition();
    double pos_delta = mass_object_.position - position.y;

    position.y = mass_object_.position;

    mass_object_.render_object->moveTo(position);
    spring_.render_object->move(glm::vec3(0, pos_delta, 0));
}

}