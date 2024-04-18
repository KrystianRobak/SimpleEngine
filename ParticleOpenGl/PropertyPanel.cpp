#include "PropertyPanel.h"
#include "AssetManager.h"


void PropertyPanel::Render(SceneView* scene_view)
{
    auto models = AssetManager::GetInstance()->GetModels();

    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SameLine(0, 5.0f);
        ImGui::Text("mCurrentFile.c_str()");
    }

    if (ImGui::CollapsingHeader("Objects"))
    {
        for (int i = 0; i < models.size(); i++) {
            models[i]->GenerateGUIElements(i);
        }
    }

    ImGui::End();
}