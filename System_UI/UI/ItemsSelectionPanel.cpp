#include "ItemsSelectionPanel.h"
#include "Coordinator.h"

void ItemsSelectionPanel::Render()
{
    std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

    ImGui::Begin("SelectionPanel");
    if (ImGui::CollapsingHeader("Objects"))
    {
        ImGui::Indent();

        ImGui::BeginChild("ObjectList", ImVec2(0, 150), true);
        for (int entity = 1; entity < coordinator->GetLightEntitiesAmount(); entity++)
        {
            std::string objectName = "Light " + std::to_string(entity);
            ImGui::Selectable(objectName.c_str());
            if (ImGui::IsItemClicked())
            {
                coordinator->SetSelectedEntity(entity);
            }
        }
        for (int entity = 10; entity < 10 + coordinator->GetEntitiesAmount(); entity++)
        {
            std::string objectName = "Entity " + std::to_string(entity - 10);
            ImGui::Selectable(objectName.c_str());
            if (ImGui::IsItemClicked())
            {
                coordinator->SetSelectedEntity(entity);
            }
        }
        ImGui::EndChild();
    }

    ImGui::End();
}
