#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <imgui.h>
#include "Coordinator.h"
#include "Transform.h"
#include <vector>
#include <memory>
#include <limits>
#include <string>

// Forward declarations
class CollisionSphere;
class CollisionPlane;
class CollisionBox;

enum class CollisionType
{
    noone,
    SphereSphere,
    BoxBox,
    PlanePlane,
    SpherePlane,
    SphereBox,
    BoxPlane
};

class CollisionMesh
{
public:
    virtual ~CollisionMesh() = default;

    virtual glm::vec3 FindFurthestPoint(const glm::vec3& direction) const
    {
        glm::vec3 maxPoint;
        float maxDistance = -std::numeric_limits<float>::max();

        for (const auto& vertex : vertices)
        {
            float distance = glm::dot(vertex, direction);
            if (distance > maxDistance)
            {
                maxDistance = distance;
                maxPoint = vertex;
            }
        }

        return maxPoint;
    }

    std::vector<glm::vec3> vertices;
};

class CollisionPlane : public CollisionMesh
{
public:
    glm::vec3 plane;
    float distance;
};

class CollisionBox : public CollisionMesh
{
public:
    glm::vec3 vecMax;
    glm::vec3 vecMin;
};

class CollisionSphere : public CollisionMesh
{
public:
    glm::vec3* centerPoint;
    float radius;
};

class Collider
{
public:
    void GenerateGUIElements(std::int32_t entity)
    {
        std::string label = "CollisionSphere##" + std::to_string(entity);
        if (ImGui::Button(label.c_str()))
        {
            std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
            auto& transform = coordinator->GetComponent<Transform>(entity);

            auto colliderSphere = new CollisionSphere();
            colliderSphere->centerPoint = &transform.position;
            colliderSphere->radius = 0.5f;

            collider = colliderSphere;
        }
        label = "CollisionBox##" + std::to_string(entity);
        if (ImGui::Button(label.c_str()))
        {
            auto colliderBox = new  CollisionBox();
            collider = colliderBox;
        }
        label = "CollisionPlane##" + std::to_string(entity);
        if (ImGui::Button(label.c_str()))
        {
            auto colliderPlane = new CollisionPlane();
            collider = colliderPlane;
        }
    }

public:
    CollisionMesh* collider;
};

class CollisionHandler {
public:
    static std::pair<CollisionType, bool> HandleCollision(CollisionMesh* planeCollider, CollisionMesh* planeCollider2);
    static std::pair<CollisionType, bool> HandleCollision(CollisionPlane* planeCollider, CollisionPlane* planeCollider2);
    static std::pair<CollisionType, bool> HandleCollision(CollisionPlane* planeCollider, CollisionSphere* sphereCollider);
    static std::pair<CollisionType, bool> HandleCollision(CollisionPlane* planeCollider, CollisionBox* boxCollider);
    static std::pair<CollisionType, bool> HandleCollision(CollisionBox* boxCollider, CollisionSphere* sphereCollider);
    static std::pair<CollisionType, bool> HandleCollision(CollisionBox* boxCollider, CollisionBox* boxCollider2);
    static std::pair<CollisionType, bool> HandleCollision(CollisionBox* boxCollider, CollisionPlane* planeCollider);
    static std::pair<CollisionType, bool> HandleCollision(CollisionSphere* sphereCollider, CollisionSphere* sphereCollider2);
    static std::pair<CollisionType, bool> HandleCollision(CollisionSphere* sphereCollider, CollisionPlane* planeCollider);
    static std::pair<CollisionType, bool> HandleCollision(CollisionSphere* sphereCollider, CollisionBox* boxCollider);
    
};



