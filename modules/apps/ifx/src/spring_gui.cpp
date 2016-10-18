#include <gui/imgui/imgui.h>
#include "spring_gui.h"

#include <string>
#include <iostream>

SpringGUI::SpringGUI(GLFWwindow* window,
                     ifx::SpringSimulation1D* simulation) :
        ifx::GUI(window),
        simulation_(simulation){
    SetDefaultParameters();
}

SpringGUI::~SpringGUI(){

}

void SpringGUI::SetDefaultParameters(){
    next_parameters_.initial_mass_object.position = 0.0f;
    next_parameters_.initial_mass_object.velocity = 0.1f;
    next_parameters_.initial_mass_object.mass = 10.0f;
    next_parameters_.initial_mass_object.render_object
            = simulation_->mass_object()->render_object;

    next_parameters_.initial_spring.damping_factor = 0.2f;
    next_parameters_.initial_spring.spring_factor = 0.1f;
    next_parameters_.initial_spring.amplitude = 1.00f;
    next_parameters_.initial_spring.frequency = 0.1f;
    next_parameters_.initial_spring.phase_shift = 0.1f;
    next_parameters_.initial_spring.equilibrium_function
            = ifx::ShiftFunction::CONSTANT;
    next_parameters_.initial_spring.external_field_function
            =ifx::ShiftFunction::CONSTANT;
    next_parameters_.initial_spring.render_object
            = simulation_->spring()->render_object;

    next_parameters_.time_delta = 0.005;
}

void SpringGUI::Render(){
    NewFrame();

    ImGui::SetNextWindowSize(ImVec2(350,550), ImGuiSetCond_Always);
    ImGui::Begin("Spring");
    if(ImGui::CollapsingHeader("Controls"), 1)
        RenderControls();
    if(ImGui::CollapsingHeader("Simulation"), 1)
        RenderInfo();
    if(ImGui::CollapsingHeader("Mass Object"), 1)
        RenderMassParameters();
    if(ImGui::CollapsingHeader("Spring Object"), 1)
        RenderSpringParameters();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(350, 750), ImGuiSetCond_Always);
    ImGui::Begin("Plots");
    if(ImGui::CollapsingHeader("Forces"), 1)
        RenderForcePlot();
    if(ImGui::CollapsingHeader("Mass"), 1)
        RenderMassPlot();

    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(400,400), ImGuiSetCond_Appearing);
    ImGui::Begin("Configuration Space");
    RenderConfigurationPlot();
    ImGui::End();

    ImGui::Render();
}

void SpringGUI::RenderControls(){
    ImGui::Text("F1: Scene Controls");
    ImGui::Text("F2: GUI Controls");
    ImGui::Text("Set parameters\nand press Reset to apply");
}

void SpringGUI::RenderInfo(){
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Time: %.2f [s]", simulation_->total_time());

    if (ImGui::Button("Reset")) {
        simulation_->SetRunning(true);
        simulation_->Reset(next_parameters_);
    }
    ImGui::SameLine();

    std::string play_button_text;
    if (simulation_->IsRunning())
        play_button_text = "Pause";
    else
        play_button_text = "Play";

    if (ImGui::Button(play_button_text.c_str())) {
        simulation_->SetRunning(!simulation_->IsRunning());
    }
}

void SpringGUI::RenderMassParameters(){
    ImGui::SliderFloat("mass", &next_parameters_.initial_mass_object.mass,
                       0.1f, 10.0f);
    ImGui::SliderFloat("position",
                       &next_parameters_.initial_mass_object.position,
                       -1.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("velocity",
                       &next_parameters_.initial_mass_object.velocity,
                       -10.0f, 10.0f, "%.6f");
}

void SpringGUI::RenderSpringParameters(){
    const int item_count = 4;
    const char *items[] = {"Constant",
                           "Jumping",
                           "Jumping Contant",
                           "Sinuosidal"};
    static int current_equilibrium_item = 0;
    static int current_external_item = 0;
    ImGui::Combo("Equilibrium Function", &current_equilibrium_item,
                 items, item_count);
    ImGui::Combo("External Field Function", &current_external_item,
                 items, item_count);
    next_parameters_.initial_spring.equilibrium_function
            = GetShiftFunction(current_equilibrium_item);
    next_parameters_.initial_spring.external_field_function
            = GetShiftFunction(current_external_item);

    ImGui::SliderFloat("Damping Factor",
                       &next_parameters_.initial_spring.damping_factor,
                       0.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("Spring Factor",
                       &next_parameters_.initial_spring.spring_factor,
                       0.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("Amplitude",
                       &next_parameters_.initial_spring.amplitude,
                       0.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("Frequency",
                       &next_parameters_.initial_spring.frequency,
                       0.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("Phase Shift",
                       &next_parameters_.initial_spring.phase_shift,
                       0.0f, 1.0f, "%.6f");
    ImGui::SliderFloat("Time delta [s]",
                       &next_parameters_.time_delta,
                       0.001f, 0.1f, "%.6f");
}

void SpringGUI::RenderForcePlot(){
    std::vector<float>& spring_force = simulation_->spring_cache().spring_force;
    std::vector<float>& damping_force
            = simulation_->spring_cache().damping_force;
    std::vector<float>& external_force
            = simulation_->spring_cache().external_force;
    std::vector<float>& equilibrium_function
            = simulation_->spring_cache().equilibrium_function;
    ImGui::PlotLines("Spring Force: f(t)",
                     spring_force.data(),
                     spring_force.size(),
                     0,
                     "f(t)",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));

    ImGui::PlotLines("Damping Force: g(t)",
                     damping_force.data(),
                     damping_force.size(),
                     0,
                     "g(t)",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));

    ImGui::PlotLines("External Force: h(t)",
                     external_force.data(),
                     external_force.size(),
                     0,
                     "h(t)",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));
    ImGui::PlotLines("Equilibrium: w(t)",
                     equilibrium_function.data(),
                     equilibrium_function.size(),
                     0,
                     "w(t)",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));

}

void SpringGUI::RenderMassPlot(){
    std::vector<float>& positions = simulation_->spring_cache().positions_;
    std::vector<float>& velocities = simulation_->spring_cache().velocities_;
    std::vector<float>& accelerations
            = simulation_->spring_cache().accelerations_;

    ImGui::PlotLines("Position",
                     positions.data(),
                     positions.size(),
                     0,
                     "x",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));

    ImGui::PlotLines("Velocity",
                     velocities.data(),
                     velocities.size(),
                     0,
                     "v",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));

    ImGui::PlotLines("Acceleration",
                     accelerations.data(),
                     accelerations.size(),
                     0,
                     "a",
                     FLT_MAX, FLT_MAX, ImVec2(0,80));
}

void SpringGUI::RenderConfigurationPlot(){
    std::vector<float>& positions = simulation_->spring_cache().positions_;
    std::vector<float>& velocities = simulation_->spring_cache().velocities_;

    static ImVec4 col = ImVec4(1.0f,1.0f,0.4f,1.0f);
    const ImU32 col32 = ImColor(col);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 p = ImGui::GetCursorScreenPos();

    float scale = 80.0f;
    float offset = 200.0f;
    float offset_pos = 0.0f;
    float offset_vel = 0.0f;
    for(int i = 1; i < positions.size(); i++){
        float x = p.x + offset + (positions[i-1] + offset_pos) * scale;
        float y = p.y + offset + (velocities[i-1] + offset_vel)* scale;

        float x1 = p.x + offset + (positions[i] + offset_pos) * scale;
        float y1 = p.y + offset + (velocities[i] + offset_vel)* scale;
        draw_list->AddLine(ImVec2(x, y),
                           ImVec2(x1, y1), col32, 0.5f);
    }
}

ifx::ShiftFunction SpringGUI::GetShiftFunction(int id){
    if(id == 0)
        return ifx::ShiftFunction::CONSTANT;
    if(id == 1)
        return ifx::ShiftFunction::JUMPING;
    if(id == 2)
        return ifx::ShiftFunction::JUMPING_CONST;
    if(id == 3)
        return ifx::ShiftFunction::SINUSOIDAL;
}
