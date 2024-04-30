#include "ItemsSelectionPanel.h"
#include "Coordinator.h"

void ItemsSelectionPanel::Render()
{
    Coordinator* coordinator = Coordinator::GetCoordinator();

    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Objects"))
    {
        ImGui::Indent();
        for (int entity = 1; entity < coordinator->GetEntitiesAmount(); entity++)
        {
            
        }
    }

    ImGui::End();
}
