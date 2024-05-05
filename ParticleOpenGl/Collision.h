#pragma once

#include <glm.hpp>
#include <vector>

struct CollisionPlane : CollisionMesh
{

};

struct CollisionBox : CollisionMesh
{
    glm::vec3 vecMax;
    glm::vec3 vecMin;
};

struct CollisionSphere : CollisionMesh
{
    glm::vec3 centerPoint;
    float radius;
};

const std::vector<const char* const> meshes = {"CollisionBox","CollisionSphere", "CollisionPlane"};
const char* current_item = NULL;

struct Collider
{
    CollisionMesh aa;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string label = "Object##" + entity;

        label = "Gravity## " + entity;

        if (ImGui::BeginCombo("##Meshes", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < meshes.size(); n++)
            {
                bool is_selected = (current_item == meshes[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(meshes[n], is_selected))
                    current_item = meshes[n];
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }
};

struct CollisionMesh
{
};





static bool MyAABBtoAABB(const CollisionBox& box1, const CollisionBox& box2);
static bool MySphereToSphere(const CollisionSphere& tSph1, const CollisionSphere& tSph2);

static bool MySphereToSphere(const CollisionSphere& tSph1, const CollisionSphere& tSph2)
{
    // Calculate the squared distance between the centers of both spheres
    glm::vec3 vecDist = tSph2.centerPoint - tSph1.centerPoint;
    float fDistSq = glm::dot(vecDist, vecDist);

    // Calculate the squared sum of both radii
    float fRadiiSumSquared = (tSph1.radius + tSph2.radius) * (tSph1.radius + tSph2.radius);

    // Check for collision
    // If the distance squared is less than or equal to the square sum
    // of the radii, then we have a collision
    if (fDistSq <= fRadiiSumSquared)
        return true;

    // If not, then return false
    return false;
}




static bool MyAABBtoAABB(const CollisionBox& tBox1, const CollisionBox& tBox2)
{
    return(tBox1.vecMax.x > tBox2.vecMin.x &&
        tBox1.vecMin.x < tBox2.vecMax.x &&
        tBox1.vecMax.y > tBox2.vecMin.y &&
        tBox1.vecMin.y < tBox2.vecMax.y &&
        tBox1.vecMax.z > tBox2.vecMin.z &&
        tBox1.vecMin.z < tBox2.vecMax.z);
}