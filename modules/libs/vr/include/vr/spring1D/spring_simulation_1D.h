#ifndef PROJECT_SPRING1D_H
#define PROJECT_SPRING1D_H

#include <vr/simulation.h>
#include <math/math_ifx.h>

#include <vector>

class RenderObject;

/**
 * Simulation of 1D spring.
 * Only interested in one dimension of the position.
 * Glossary:
 *  mass:                       m
 *  position:                   x
 *  velocity:                   x_t
 *  acceleration:               x_tt
 *  damping_factor:             k
 *  spring_factor:              c
 *  equilibrium_function:       w(t)
 *  external_field_function:    h(t)
 *  amplitude:                  A
 *  frequency:                  omega
 *  phase_shift:                phi (?)
 *  spring_force:               f
 *  damping_force:              g
 *  external_force:             h
 */

namespace ifx {

/**
 * The type of the shift function for:
 *      w - function of equilibrium shift.
 *      h - external field force.
 */
enum class ShiftFunction{
    CONSTANT = 0,
    JUMPING,
    JUMPING_CONST,
    SINUSOIDAL
};

/**
 * Description of the mass object.
 */
struct MassObject {
    float previous_position;
    float position;
    float velocity;

    float mass;

    RenderObject* render_object;
};

struct Spring {
    float damping_factor;
    float spring_factor;

    float amplitude;
    float frequency;
    float phase_shift;

    ShiftFunction equilibrium_function = ShiftFunction::CONSTANT;
    ShiftFunction external_field_function = ShiftFunction::CONSTANT;

    RenderObject* render_object;
};

/**
 * The Parameters for the simulation.
 */
struct Spring1DParameters{
    MassObject initial_mass_object;
    Spring initial_spring;

    float time_delta;
};

/**
 * Used to store simulation data, e.g. for plotting.
 */
struct SpringCache{
    std::vector<float> positions_;
    std::vector<float> velocities_;
    std::vector<float> accelerations_;

    std::vector<float> spring_force;
    std::vector<float> damping_force;
    std::vector<float> external_force;
    std::vector<float> equilibrium_function;
};


class SpringSimulation1D : public Simulation{
public:

    SpringSimulation1D(const Spring1DParameters& params);
    ~SpringSimulation1D();

    double total_time() {return total_time_s_;}
    MassObject* mass_object(){return &mass_object_;}
    Spring* spring(){return &spring_;}
    SpringCache& spring_cache() {return spring_cache_;}

    void Reset(const Spring1DParameters& params);
    void Update();

private:
    double ComputeNextPosition();

    double ComputeEquilibriumShift();
    double ComputeExternalFieldForce();

    /**
     * Compute the shift function based on chosen function.
     */
    double ComputeShiftFunction(ShiftFunction shift_function);
    double ComputeConstantFunction();
    double ComputeJumpingFunction();
    double ComputeJumpingConstantFunction();
    double ComputeSinusoidalFunction();

    bool SatisfiesTimeDelta();

    void UpdateCache(double prev_position,
                     double current_position,
                     double next_position);
    void ClearCache();

    /**
     * Updates the actual position of render bodies in the simulation.
     */
    void UpdateObjects();

    MassObject mass_object_;
    Spring spring_;

    // In seconds.
    double time_delta_;
    double time_delta_sqr_;

    double current_update_time_;
    double last_update_time_;

    double total_time_s_;

    SpringCache spring_cache_;
};
}

#endif //PROJECT_SPRING1D_H
