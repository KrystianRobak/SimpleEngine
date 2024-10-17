#include "PropertyPanel.h"
#include "Renderable.h"
#include "Gravity.h"
#include "RigidBody.h"
#include "Collision.h"
#include "Player.h"


inline std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void RenderComponentsMenu(std::int32_t& entity, std::bitset<32>& signature) 
{
    std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

    if (ImGui::CollapsingHeader("Add component"))
    {
        if (!signature.test(coordinator->GetComponentType<Transform>()))
        {
            if (ImGui::Button("Transform"))
            {
                coordinator->AddComponent(
                    entity,
                    Transform{
                        .position = glm::vec3(1, 1, -30),
                        .rotation = glm::vec3(0, 0.1, 0),
                        .scale = glm::vec3(3, 3, 3)
                    });
            }
        }
        if (!signature.test(coordinator->GetComponentType<Gravity>()))
        {
            if (ImGui::Button("Gravity"))
            {
                coordinator->AddComponent<Gravity>(
                    entity,
                    { glm::vec3(0.0f, 0, 0.0f) });
            }
        }
        if (!signature.test(coordinator->GetComponentType<Player>()))
        {
            if (ImGui::Button("Player"))
            {

            }
        }
        if (!signature.test(coordinator->GetComponentType<Renderable>()))
        {
            if (ImGui::Button("Renderable"))
            {
                coordinator->AddComponent(
                    entity,
                    Renderable{
                        .color = glm::vec4(40,40,40, 1)
                    });
            }
        }
        if (!signature.test(coordinator->GetComponentType<RigidBody>()))
        {
            if (ImGui::Button("RigidBody"))
            {
                coordinator->AddComponent(
                    entity,
                    RigidBody{
                        .velocity = glm::vec3(0.0f, 0.0f, 0.0f),
                        .acceleration = glm::vec3(0.0f, 0.0f, 0.0f)
                    });
            }
        }
        if (!signature.test(coordinator->GetComponentType<StaticMesh>()))
        {
            if (ImGui::Button("StaticMesh"))
            {
                coordinator->AddComponent(
                    entity,
                    StaticMesh{

                    });
            }
        }
        if (!signature.test(coordinator->GetComponentType<Collider>()))
        {
            if (ImGui::Button("Collision"))
            {
                coordinator->AddComponent(
                    entity,
                    Collider{
                    });
            }
        }
    }

    if (ImGui::CollapsingHeader("Remove component"))
    {
        if (signature.test(coordinator->GetComponentType<Transform>()))
        {
            if (ImGui::Button("Transform"))
            {
                coordinator->RemoveComponent<Transform>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<Gravity>()))
        {
            if (ImGui::Button("Gravity"))
            {
                coordinator->RemoveComponent<Gravity>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<Player>()))
        {
            if (ImGui::Button("Player"))
            {
                coordinator->RemoveComponent<Player>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<Renderable>()))
        {
            if (ImGui::Button("Renderable"))
            {
                coordinator->RemoveComponent<Renderable>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<RigidBody>()))
        {
            if (ImGui::Button("RigidBody"))
            {
                coordinator->RemoveComponent<RigidBody>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<StaticMesh>()))
        {
            if (ImGui::Button("StaticMesh"))
            {
                coordinator->RemoveComponent<StaticMesh>(entity);
            }
        }
        if (signature.test(coordinator->GetComponentType<Collider>()))
        {
            if (ImGui::Button("Collision"))
            {
                coordinator->RemoveComponent<Collider>(entity);
            }
        }


    }

}


void PropertyPanel::Render()
{
    std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
    std::int32_t entity = coordinator->GetSelectedEntity();
    if (!entity)
        return;

    std::bitset<32> signature = coordinator->GetEntitySignature(entity);
    ImGui::Begin("Properties");
    RenderComponentsMenu(entity, signature);
    signature = coordinator->GetEntitySignature(entity);
   

    std::string label = "Components: ##" + std::to_string(entity);

   /* if (signature.test(coordinator->GetComponentType<Transform>()))
    {
        coordinator->GetComponent<Transform>(entity).GenerateGUIElements(entity);
    }

    if (signature.test(coordinator->GetComponentType<Renderable>()))
    {
        coordinator->GetComponent<Renderable>(entity).GenerateGUIElements(entity);
    }

    if (signature.test(coordinator->GetComponentType<Gravity>()))
    {
        coordinator->GetComponent<Gravity>(entity).GenerateGUIElements(entity);
    }

    if (signature.test(coordinator->GetComponentType<RigidBody>()))
    {
        coordinator->GetComponent<RigidBody>(entity).GenerateGUIElements(entity);
    }

    if (signature.test(coordinator->GetComponentType<Collider>()))
    {
        coordinator->GetComponent<Collider>(entity).GenerateGUIElements(entity);
    }*/

    ImGui::Text(label.c_str());
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DIRECTORY_ENTRY"))
        {
            if (payload->DataSize > 0) 
            {
                std::string nameWithPath(static_cast<const char*>(payload->Data));
                std::vector<std::string> parts = splitString(nameWithPath, '|');
                if (parts.size() == 2) 
                {
                    std::string name = parts[0];
                    std::string path = parts[1];
                    auto& staticMesh = coordinator->GetComponent<StaticMesh>(entity);
                    staticMesh.loadModel(path);
                }
            }
        }
    ImGui::EndDragDropTarget();
    }

    ImGui::End();
}


// TRANSFORM
//void GenerateGUIElements(std::uint32_t entity)
//{
//    std::string entityStr = std::to_string(entity);
//
//    std::string transformLabel = "Transform##" + entityStr;
//    ImGui::Text("%s", transformLabel.c_str());
//
//    std::string positionLabel = "Position##" + entityStr;
//    ImGui::SliderFloat3(positionLabel.c_str(), &position[0], -30.f, 30.f);
//
//    std::string rotationLabel = "Rotation##" + entityStr;
//    ImGui::SliderFloat3(rotationLabel.c_str(), &rotation[0], 0.f, 1.f);
//
//    std::string scaleLabel = "Scale##" + entityStr;
//    ImGui::SliderFloat3(scaleLabel.c_str(), &scale[0], -15.f, 15.f);
//}


// THRUST
//void GenerateGUIElements(std::uint32_t entity)
//{
//    std::string label = "Object##" + entity;
//    if (ImGui::CollapsingHeader(label.c_str()))
//    {
//        label = "Thrust## " + entity;
//        ImGui::SliderFloat3(label.c_str(), &force[0], -15.f, 15.f);
//    }
//}


// RENDERABLE
//void GenerateGUIElements(std::uint32_t entity)
//{
//    std::string entityStr = std::to_string(entity);
//
//    std::string colorLabel = "Color##" + entityStr;
//    ImGui::ColorPicker4(colorLabel.c_str(), &color[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
//}


// RIGIDBODY
//void GenerateGUIElements(std::uint32_t entity)
//{
//    std::string entityStr = std::to_string(entity);
//
//    std::string velocityLabel = "Velocity##" + entityStr;
//    ImGui::SliderFloat3(velocityLabel.c_str(), &velocity[0], -20.f, 20.f);
//
//    std::string massLabel = "Mass##" + entityStr;
//    ImGui::InputFloat(massLabel.c_str(), &mass);
//
//    std::string accelerationLabel = "Acceleration##" + entityStr;
//    ImGui::SliderFloat3(accelerationLabel.c_str(), &acceleration[0], -15.f, 15.f);
//}

// CAMERA
//void GenerateGUIElements(std::uint32_t entity)
//{
//       if (ImGui::CollapsingHeader(""))
//       {
//           // Add the "Delete" button
//           std::string label = "Delete##" + entity;
//           if (ImGui::Button(label.c_str(), ImVec2(-1, 0)))
//           {
//               
//           }
//           // Proceed with other GUI elements as before
//           label = "Position##" + entity;
//           ImGui::SliderFloat3(label.c_str(), &cameraPos[0], -15.f, 15.f);
//           ImGui::BeginGroup();
//           label = "AxisX" + name + std::to_string(index);
//           ImGui::Checkbox(label.c_str(), &axis[0]);
//           label = "AxisY" + name + std::to_string(index);
//           ImGui::Checkbox(label.c_str(), &axis[1]);
//           label = "AxisZ" + name + std::to_string(index);
//           ImGui::EndGroup();
//           label = "Angle " + name + std::to_string(index);
//           ImGui::SliderFloat(label.c_str(), &angle, 0.f, 360.f);
//           ImGui::BeginGroup();
//           label = "Texture" + name + std::to_string(index);
//           ImGui::Checkbox(label.c_str(), &texture);
//           label = "Lightning" + name + std::to_string(index);
//           ImGui::Checkbox(label.c_str(), &lightning);
//           label = "Color Picker" + name + std::to_string(index);
//           ImGui::ColorPicker4(label.c_str(), color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
//           ImGui::EndGroup();
//       }
//}

// COLLISION
//void GenerateGUIElements(std::int32_t entity)
//{
//    std::string label = "CollisionSphere##" + std::to_string(entity);
//    if (ImGui::Button(label.c_str()))
//    {
//        std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
//        auto& transform = coordinator->GetComponent<Transform>(entity);
//
//        auto colliderSphere = new CollisionSphere();
//        colliderSphere->centerPoint = &transform.position;
//        colliderSphere->radius = 0.5f;
//
//        collider = colliderSphere;
//    }
//    label = "CollisionBox##" + std::to_string(entity);
//    if (ImGui::Button(label.c_str()))
//    {
//        auto colliderBox = new  CollisionBox();
//        collider = colliderBox;
//    }
//    label = "CollisionPlane##" + std::to_string(entity);
//    if (ImGui::Button(label.c_str()))
//    {
//        auto colliderPlane = new CollisionPlane();
//        collider = colliderPlane;
//    }
//}

// GRAVITY
//void GenerateGUIElements(std::uint32_t entity)
//{
//    std::string entityStr = std::to_string(entity);
//
//    std::string gravityLabel = "Gravity##" + entityStr;
//    ImGui::SliderFloat3(gravityLabel.c_str(), &force[0], -15.f, 15.f);
//}