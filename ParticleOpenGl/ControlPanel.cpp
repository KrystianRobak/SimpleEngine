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
    ImGui::End();
}
