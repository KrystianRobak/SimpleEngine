#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "Coordinator.h"
#include "Transform.h"
#include <vector>
#include <array>

class CollisionSphere;
class CollisionPlane;
class CollisionBox;

enum ColliderType
{
    Sphere,
    Plane,
    Box
};

class CollisionMesh
{
public:
    virtual ~CollisionMesh() {}

    virtual bool CollisionHandling(CollisionMesh* collider) = 0;

    virtual glm::vec3 FindFurthestPoint(glm::vec3 direction) const
    {
        glm::vec3 maxPoint;
        float maxDistance = -FLT_MAX;

        for (glm::vec3 vertex : vertices)
        {
            float distance = glm::dot<3, float, glm::qualifier::highp>(vertex, direction);
            if (distance > maxDistance)
            {
                maxDistance = distance;
                maxPoint = vertex;
            }
        }

        return maxPoint;
    }

    std::vector<glm::vec3> vertices;
    ColliderType colliderType;
};

class CollisionPlane : public CollisionMesh
{
public:
    glm::vec3 plane;
    float distance;

    bool CollisionHandling(CollisionMesh* collider) override
    {
        // Dynamic cast to check the actual type of the collider
        if (auto planeCollider = dynamic_cast<CollisionPlane*>(collider)) {
            // Handle collision between two planes
            return CollisionHandler(planeCollider);
        }
        else if (auto sphereCollider = dynamic_cast<CollisionSphere*>(collider)) {
            // Handle collision between a plane and a sphere
            return CollisionHandler(sphereCollider);
        }
        else if (auto boxCollider = dynamic_cast<CollisionBox*>(collider)) {
            // Handle collision between a plane and a box
            return CollisionHandler(boxCollider);
        }
        return false; // Default case: no collision
    }

    bool CollisionHandler(CollisionPlane* planeCollider)
    {
        // Collision handling logic for plane-plane collision
        return false;
    }

    bool CollisionHandler(CollisionSphere* sphereCollider)
    {
        // Collision handling logic for plane-sphere collision
        return false;
    }

    bool CollisionHandler(CollisionBox* boxCollider)
    {
        // Collision handling logic for plane-box collision
        return false;
    }
};

class CollisionBox : public CollisionMesh
{
public:
    glm::vec3 vecMax;
    glm::vec3 vecMin;

    bool CollisionHandling(CollisionMesh* collider) override
    {
        // Dynamic cast to check the actual type of the collider
        if (auto planeCollider = dynamic_cast<CollisionPlane*>(collider)) {
            // Handle collision between a box and a plane
            return CollisionHandler(planeCollider);
        }
        else if (auto sphereCollider = dynamic_cast<CollisionSphere*>(collider)) {
            // Handle collision between a box and a sphere
            return CollisionHandler(sphereCollider);
        }
        else if (auto boxCollider = dynamic_cast<CollisionBox*>(collider)) {
            // Handle collision between two boxes
            return CollisionHandler(boxCollider);
        }
        return false; // Default case: no collision
    }

    bool CollisionHandler(CollisionPlane* planeCollider)
    {
        // Collision handling logic for box-plane collision
        return false;
    }

    bool CollisionHandler(CollisionSphere* sphereCollider)
    {
        // Collision handling logic for box-sphere collision
        return false;
    }

    bool CollisionHandler(CollisionBox* boxCollider)
    {
        // Collision handling logic for box-box collision
        return false;
    }
};

class CollisionSphere : public CollisionMesh
{
public:
    glm::vec3* centerPoint;
    float radius;

    bool CollisionHandling(CollisionMesh* collider) override
    {
        // Dynamic cast to check the actual type of the collider
        
        if (auto planeCollider = dynamic_cast<CollisionPlane*>(collider)) {
            // Handle collision between a sphere and a plane
            return CollisionHandler(planeCollider);
        }
        else if (auto sphereCollider = dynamic_cast<CollisionSphere*>(collider)) {
            // Handle collision between two spheres
            return CollisionHandler(sphereCollider);
        }
        else if (auto boxCollider = dynamic_cast<CollisionBox*>(collider)) {
            // Handle collision between a sphere and a box
            return CollisionHandler(boxCollider);
        }
        return false; // Default case: no collision
    }

    bool CollisionHandler(CollisionPlane* planeCollider)
    {
        // Collision handling logic for sphere-plane collision
        return false;
    }

    bool CollisionHandler(CollisionSphere* sphereCollider)
    {
        glm::vec3 distance = *centerPoint - *sphereCollider->centerPoint;

        float distMag = glm::length(distance);

        float sumRadii = radius + sphereCollider->radius;
        bool isColliding = distMag < sumRadii;

        return isColliding;
    }

    bool CollisionHandler(CollisionBox* boxCollider)
    {
        // Collision handling logic for sphere-box collision
        return false;
    }
};

struct Collider
{
    CollisionMesh* collider;

    void GenerateGUIElements(std::int32_t entity)
    {
        std::string label = "CollisionSphere##" + entity;
        if (ImGui::Button(label.c_str()))
        {
            Coordinator* coordinator = Coordinator::GetCoordinator();
            auto& transform = coordinator->GetComponent<Transform>(entity);

            delete collider;
            auto colliderSphere = new CollisionSphere;
            colliderSphere->centerPoint = &transform.position;
            colliderSphere->radius = 0.5f;

            collider = colliderSphere;
            collider->colliderType = ColliderType::Sphere;
        }
        label = "CollisionBox##" + entity;
        if (ImGui::Button(label.c_str()))
        {
            delete collider;
            collider = new CollisionBox;
            collider->colliderType = ColliderType::Box;
        }
        label = "CollisionPlane##" + entity;
        if (ImGui::Button(label.c_str()))
        {
            delete collider;
            collider = new CollisionPlane;
            collider->colliderType = ColliderType::Plane;
        }
    }
};