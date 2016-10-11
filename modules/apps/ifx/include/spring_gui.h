#ifndef PROJECT_SPRING_GUI_H
#define PROJECT_SPRING_GUI_H

#include <gui/gui.h>
#include "vr/spring1D/spring_simulation_1D.h"

class SpringGUI : public ifx::GUI {
public:

    SpringGUI(GLFWwindow* window, ifx::SpringSimulation1D* simulation);
    ~SpringGUI();

    virtual void Render() override;

private:
    void SetDefaultParameters();

    void RenderControls();
    void RenderInfo();
    void RenderMassParameters();
    void RenderSpringParameters();

    void RenderForcePlot();
    void RenderMassPlot();
    void RenderConfigurationPlot();

    ifx::ShiftFunction GetShiftFunction(int id);

    ifx::Spring1DParameters next_parameters_;
    ifx::SpringSimulation1D* simulation_;
};


#endif //PROJECT_SPRING_GUI_H
