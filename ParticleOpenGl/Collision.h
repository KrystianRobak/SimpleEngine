#pragma once

#include <../glm.hpp>



struct CollisionPlane
{

};



struct CollisionBox
{
    glm::vec3 vecMax;
    glm::vec3 vecMin;
};

struct CollisionSphere
{
    glm::vec3 centerPoint;
    float radius;
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