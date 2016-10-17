#ifndef PROJECT_SPRING1D_H
#define PROJECT_SPRING1D_H

#include <vr/simulation.h>
#include <math/math_ifx.h>

class RenderObject;

/**
 * Simulation of 1D spring.
 * Only interested in one dimension of the position.
 *
 *
 */

namespace ifx {

/**
 * The type of the shift function for:
 *      w - function of equilibrium shift.
 *      h - external field force.
 */
enum class ShiftFunction{
    CONSTANT,
    JUMPING,
    JUMPING_CONST,
    SINUSOIDAL
};

/**
 * Description of the mass object.
 */
struct MassObject {
    double previous_position;
    double position;
    double velocity;

    double mass;

    RenderObject* render_object;
};

struct Spring {
    double damping_factor;
    double spring_factor;

    double amplitude;
    double frequency;
    double phase_shift;

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

    double time_delta;
};


class SpringSimulation1D : public Simulation{
public:

    SpringSimulation1D(const Spring1DParameters& params);
    ~SpringSimulation1D();

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

    /**
     * Updates the actual position of render bodies in the simulation.
     */
    void UpdateObjects();

    MassObject mass_object_;
    Spring spring_;

    // In seconds.
    const double time_delta_;
    const double time_delta_sqr_;

    double current_update_time_;
    double last_update_time_;
};
}

#endif //PROJECT_SPRING1D_H
