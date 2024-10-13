#include "ControlPanel.h"

void ControlPanel::Render()
{
    ImGui::Begin("ControlPanel");

        ImGui::BeginGroup();
        if (ImGui::Button("Start/Pause"))
        {
            std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
            coordinator->SendEvent(Events::Application::TOGGLE);
        }
        ImGui::EndGroup();
        ImGui::BeginGroup();
        if (ImGui::Button("Recompile shader"))
        {
            std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
            coordinator->SendEvent(Events::Application::RECOMPILE_SHADER);
        }
        ImGui::EndGroup();
    ImGui::End();
}
