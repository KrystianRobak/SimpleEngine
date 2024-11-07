#define SYSTEMINTERFACE_EXPORTS
#include "PhysicsSystem.h"

#include "coordinator.h"

#include "Gravity.h"
#include "RigidBody.h"
#include "Thrust.h"
#include "Transform.h"

#include <memory>

bool PhysicsSystem::Initialize()
{
	return true;
}

void PhysicsSystem::Execute(float dt)
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	for (auto const& entityA : mEntities)
	{

		auto& transform = coordinator->GetComponent<Transform>(entityA);
		// Forces
		auto const& gravity = coordinator->GetComponent<Gravity>(entityA);

		auto& rigidBody = coordinator->GetComponent<RigidBody>(entityA);
		
		glm::vec3 speed = rigidBody.velocity * dt * 24.f;

		transform.position += rigidBody.velocity * dt * 24.f;

		rigidBody.velocity += gravity.force * dt;
	}
}

void PhysicsSystem::Cleanup()
{
}

std::string PhysicsSystem::GetName() const
{
	return "Physics System";
}

extern "C" {

	SYSTEMINTERFACE_API SystemInterface* CreatePlugin()
	{
		return new PhysicsSystem();
	}

	SYSTEMINTERFACE_API void DestroyPlugin(SystemInterface* System)
	{
		delete System;
	}

}

// RESPOSITIONING


//auto sphere = dynamic_cast<CollisionSphere*>(colliderA->collider);
//
//float left = sphere->centerPoint->x - sphere->radius;
//float right = sphere->centerPoint->x + sphere->radius;
//float top = sphere->centerPoint->y + sphere->radius;
//float bottom = sphere->centerPoint->y - sphere->radius;
//
//auto& rigidBody = coordinator->GetComponent<RigidBody>(entityA);
//
//if ((left < -18 || right >= 18 || bottom < -13.5 || top > 13.5) && !rigidBody.repositioned) {
//	rigidBody.repositioned = true;
//
//	if (left < -18) {
//		sphere->centerPoint->x = -18 + sphere->radius;
//		rigidBody.velocity.x = -rigidBody.velocity.x;
//	}
//	else if (right >= 18) {
//		sphere->centerPoint->x = 18 - sphere->radius;
//		rigidBody.velocity.x = -rigidBody.velocity.x;
//	}
//	if (bottom < -13.5) {
//		sphere->centerPoint->y = -13.5 + sphere->radius;
//		rigidBody.velocity.t = -rigidBody.velocity.y;
//	}
//	else if (top > 13.5) {
//		sphere->centerPoint->y = 13.5 - sphere->radius;
//		rigidBody.velocity.y = -rigidBody.velocity.y;
//	}
//}
//else if (!(left < -18 || right >= 18 || bottom < -13.5 || top > 13.5)) {
//	rigidBody.repositioned = false;
//}