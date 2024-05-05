#include "ItemsSelectionPanel.h"
#include "Coordinator.h"

void ItemsSelectionPanel::Render()
{
    Coordinator* coordinator = Coordinator::GetCoordinator();

    ImGui::Begin("SelectionPanel");
    if (ImGui::CollapsingHeader("Objects"))
    {
        ImGui::Indent();

        ImGui::BeginChild("ObjectList", ImVec2(0, 150), true); // Adjust the size as needed
        for (int entity = 1; entity < coordinator->GetEntitiesAmount(); entity++)
        {
            std::string objectName = "Entity " + entity; // You need to implement this function
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
