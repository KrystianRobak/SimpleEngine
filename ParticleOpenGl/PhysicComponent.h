#pragma once
#include <../glm.hpp>

struct Gravity
{
	glm::vec3 force;
};

struct RigidBody
{
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};