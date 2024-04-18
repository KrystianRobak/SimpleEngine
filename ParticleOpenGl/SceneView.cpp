#include "SceneView.h"
#include "AssetManager.h"

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void SceneView::resize(int32_t width, int32_t height)
{
    size.x = width;
    size.y = height;

    frameBuffer->create_buffers((int32_t)size.x, (int32_t)size.y);
}

void SceneView::Render()
{
    AssetManager* assetManager = AssetManager::GetInstance();

    Shader* objectShader = assetManager->GetObjectShader().get();
    Shader* lightShader = assetManager->GetLightShader().get();
    
    objectShader->Use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.get()->Zoom), size.x / size.y, 0.1f, 100.0f);
    glm::mat4 view = camera.get()->GetViewMatrix();

    frameBuffer->bind();

    for (auto model : assetManager->GetModels())
    {
        model->Draw(*objectShader, projection, view);
    }

    for (auto lightSource : assetManager->GetLightSources())
    {
        //lightSource->Draw(*lightShader, projection, view);
    }

    frameBuffer->unbind();

    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    size = { viewportPanelSize.x, viewportPanelSize.y };

    uint64_t textureID = frameBuffer->get_texture();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ size.x, size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DIRECTORY_ENTRY")) {
            if (payload->DataSize > 0) {
                std::string nameWithPath(static_cast<const char*>(payload->Data));
                std::vector<std::string> parts = splitString(nameWithPath, '|'); 
                if (parts.size() == 2) {
                    std::string name = parts[0];
                    std::string path = parts[1];
                    assetManager->CreateModel(path, name);
                }
            }
        } 
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
} 