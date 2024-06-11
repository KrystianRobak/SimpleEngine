#include "AddingPanel.h"
#include "Gravity.h"
#include "Renderable.h"
#include "RigidBody.h"
#include "Collision.h"
#include <random>

void AddingPanel::Render()
{
    std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

    ImGui::Begin("AddingPanel");
    if (ImGui::CollapsingHeader("Shapes"))
    {
        ImGui::Selectable("Sphere");
        if (ImGui::IsItemClicked())
        {
            int16_t entity = coordinator->CreateEntity();
            coordinator->AddComponent(entity, Transform
                {
                    .position = glm::vec3(1, 1, -30),
                    .rotation = glm::vec3(0, 0.1, 0),
                    .scale = glm::vec3(3, 3, 3)
                });

            coordinator->AddComponent(
                entity,
                Collider{
                });

            coordinator->AddComponent(
                entity,
                StaticMesh{

                });

            coordinator->AddComponent(
                entity,
                Renderable{
                    .color = glm::vec4(40,40,40, 1)
                });

            coordinator->AddComponent<Gravity>(entity, {
                glm::vec3(0.0f, 0, 0.0f)
                });

            coordinator->AddComponent(
                entity,
                RigidBody{
                    .velocity = glm::vec3(0.0f, 0.0f, 0.0f),
                    .acceleration = glm::vec3(0.0f, 0.0f, 0.0f)
                });

            auto& staticMesh = coordinator->GetComponent<StaticMesh>(entity);
            staticMesh.loadModel("model/ball/ball.obj");

            auto& renderable = coordinator->GetComponent<Renderable>(entity);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);

            renderable.color = glm::vec4(dis(gen), dis(gen), dis(gen), 1.0f);

            auto& collider = coordinator->GetComponent<Collider>(entity);

            auto& transform = coordinator->GetComponent<Transform>(entity);

            auto colliderSphere = new CollisionSphere();
            colliderSphere->centerPoint = &transform.position;
            colliderSphere->radius = 0.5f;

            collider.collider = colliderSphere;
        }
    }

           

    ImGui::End();
}
