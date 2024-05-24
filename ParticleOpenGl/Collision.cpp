#include "Collision.h"

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionMesh* a, CollisionMesh* b) {
    if (!a || !b) {
        return std::make_pair(CollisionType::noone, false);
    }

    if (auto plane1 = dynamic_cast<CollisionPlane*>(a)) {
        if (auto plane2 = dynamic_cast<CollisionPlane*>(b)) {
            return HandleCollision(plane1, plane2);
        }
        else if (auto sphere = dynamic_cast<CollisionSphere*>(b)) {
            return HandleCollision(plane1, sphere);
        }
        else if (auto box = dynamic_cast<CollisionBox*>(b)) {
            return HandleCollision(plane1, box);
        }
    }
    else if (auto box = dynamic_cast<CollisionBox*>(a)) {
        if (auto sphere = dynamic_cast<CollisionSphere*>(b)) {
            return HandleCollision(box, sphere);
        }
        else if (auto plane = dynamic_cast<CollisionPlane*>(b)) {
            return HandleCollision(box, plane);
        }
        else if (auto box2 = dynamic_cast<CollisionBox*>(b)) {
            return HandleCollision(box, box2);
        }
    }
    else if (auto sphere = dynamic_cast<CollisionSphere*>(a)) {
        if (auto sphere2 = dynamic_cast<CollisionSphere*>(b)) {
            return HandleCollision(sphere, sphere2);
        }
        else if (auto plane = dynamic_cast<CollisionPlane*>(b)) {
            return HandleCollision(sphere, plane);
        }
        else if (auto box = dynamic_cast<CollisionBox*>(b)) {
            return HandleCollision(sphere, box);
        }
    }

    return std::make_pair(CollisionType::noone, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionPlane* planeCollider, CollisionPlane* planeCollider2)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionPlane* planeCollider, CollisionSphere* sphereCollider)
{

    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionPlane* planeCollider, CollisionBox* boxCollider)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionBox* boxCollider, CollisionSphere* sphereCollider)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionBox* boxCollider, CollisionBox* boxCollider2)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionBox* boxCollider, CollisionPlane* planeCollider)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionSphere* sphereCollider, CollisionSphere* sphereCollider2)
{
    glm::vec3 distance = *sphereCollider->centerPoint - *sphereCollider2->centerPoint;
    float distMag = glm::length(distance);
    float sumRadii = sphereCollider->radius + sphereCollider2->radius;
    return std::make_pair(CollisionType::SphereSphere, distMag < sumRadii);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionSphere* sphereCollider, CollisionPlane* planeCollider)
{

    return std::make_pair(CollisionType::SpherePlane, false);
}

std::pair<CollisionType, bool> CollisionHandler::HandleCollision(CollisionSphere* sphereCollider, CollisionBox* boxCollider)
{
    return std::make_pair(CollisionType::SpherePlane, false);
}
