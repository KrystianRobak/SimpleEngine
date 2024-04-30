#include "PropertyPanel.h"

#include "Coordinator.h"



void PropertyPanel::Render(SceneView* scene_view)
{
    Coordinator* coordinator = Coordinator::GetCoordinator();

    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Objects"))
    {
        ImGui::Indent();
        for (int entity = 1; entity < coordinator->GetEntitiesAmount(); entity++)
        {
            std::string label = "Entity: ##" + std::to_string(entity);
            if (ImGui::CollapsingHeader(label.c_str()))
            {
                ImGui::Text(label.c_str());
                
                std::string label = "Components: ##" + std::to_string(entity);
                if (ImGui::CollapsingHeader(label.c_str()))
                {
                    coordinator->GetComponent<Transform>(entity).GenerateGUIElements(entity);
                }
            }
        }
    }

    ImGui::End();
}