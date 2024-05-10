#include "PhysicsSystem.h"
#include <iostream>

#include "Gravity.h"
#include "RigidBody.h"
#include "Thrust.h"
#include "Transform.h"
#include "Collision.h"
#include "coordinator.h"
#include "Renderable.h"
#include <memory>

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	for (auto const& entityA : mEntities)
	{
		for (auto const& entityB : mEntities)
		{
			if (entityA != entityB)
			{
				std::shared_ptr<Collider> colliderA = std::make_shared<Collider>(coordinator->GetComponent<Collider>(entityA));
				std::shared_ptr<Collider> colliderB = std::make_shared<Collider>(coordinator->GetComponent<Collider>(entityB));


				if (colliderA->collider->CollisionHandling(colliderB->collider))
				{
					auto& renderableA = coordinator->GetComponent<Renderable>(entityA);
					auto& renderableB = coordinator->GetComponent<Renderable>(entityB);

					renderableA.color = { 50, 0, 0 ,1 };
					renderableB.color = { 50, 0, 0 ,1 };

					std::cout << "Hitted" << std::endl;
				}
				
				//colliderA->collider->DrawCollisionMesh();
			}
		}
		auto& rigidBody = coordinator->GetComponent<RigidBody>(entityA);
		auto& transform = coordinator->GetComponent<Transform>(entityA);
		// Forces
		auto const& gravity = coordinator->GetComponent<Gravity>(entityA);

		transform.position += rigidBody.velocity * dt * 10.f;

		rigidBody.velocity += gravity.force * dt;
	}
}