#include "PhysicsSystem.h"
#include <iostream>

#include "Gravity.h"
#include "RigidBody.h"
#include "Thrust.h"
#include "Transform.h"
#include "Collision.h"
#include "coordinator.h"

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	for (auto const& entity : mEntities)
	{
		for (auto const& entity2 : mEntities)
		{
			if (entity == entity2)
				continue;
			std::cout << MySphereToSphere(coordinator->GetComponent<CollisionSphere>(entity), coordinator->GetComponent<CollisionSphere>(entity2)) << std::endl;
		}

		auto& rigidBody = coordinator->GetComponent<RigidBody>(entity);
		auto& transform = coordinator->GetComponent<Transform>(entity);

		if (entity == 3)
			std::cout << transform.position[1];
		// Forces
		auto const& gravity = coordinator->GetComponent<Gravity>(entity);

		transform.position += rigidBody.velocity * dt;

		rigidBody.velocity += gravity.force * dt;
	}
}