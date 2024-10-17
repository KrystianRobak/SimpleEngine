#pragma once

#include <glm.hpp>

struct RigidBody
{
    float mass = 3;
	glm::vec3 velocity;
	glm::vec3 acceleration;
    glm::vec3 momentum;
    bool repositioned = false;
};
