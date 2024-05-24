#include "PhysicsSystem.h"
#include <iostream>
#include "WindowManager.h"
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
		std::shared_ptr<Collider> colliderA = std::make_shared<Collider>(coordinator->GetComponent<Collider>(entityA));

		for (auto const& entityB : mEntities)
		{
			if (entityA != entityB)
			{
				std::shared_ptr<Collider> colliderB = std::make_shared<Collider>(coordinator->GetComponent<Collider>(entityB));

				if (CollisionHandler::HandleCollision(colliderA->collider, colliderB->collider).second)
				{
					//Poprawienie pozycji kulii
					auto& rigidBodyA = coordinator->GetComponent<RigidBody>(entityA);
					auto& rigidBodyB = coordinator->GetComponent<RigidBody>(entityB);

					auto& transformA = coordinator->GetComponent<Transform>(entityA);
					auto& transformB = coordinator->GetComponent<Transform>(entityB);

					glm::vec3 pos = transformA.position - transformB.position;

					pos = glm::normalize(pos);

					transformA.position += pos * 0.1f;
					transformB.position -= pos * 0.1f;

					//Obliczenia fizyczne
					
					glm::vec3 posDifference = transformB.position - transformA.position;
					glm::vec3 velDifference = rigidBodyB.velocity - rigidBodyA.velocity;

					glm::vec3 velPosScalar = velDifference * posDifference;

					glm::vec3 direction = glm::normalize(posDifference);

					glm::vec3 momentumComponent = glm::dot(velDifference, posDifference) * direction;


					rigidBodyA.velocity = rigidBodyA.velocity + momentumComponent;
					rigidBodyB.velocity = rigidBodyB.velocity - momentumComponent;
				}
			}
		}
		
		auto sphere = dynamic_cast<CollisionSphere*>(colliderA->collider);
		
		float left = sphere->centerPoint->x - sphere->radius;
		float right = sphere->centerPoint->x + sphere->radius;
		float top = sphere->centerPoint->y + sphere->radius;
		float bottom = sphere->centerPoint->y - sphere->radius;

		auto& rigidBody = coordinator->GetComponent<RigidBody>(entityA);

		if ((left < -10 || right >= 10 || bottom < -10 || top > 10) && !rigidBody.repositioned) {
			rigidBody.repositioned = true;

			if (left < -10) {
				sphere->centerPoint->x = -10 + sphere->radius;
				rigidBody.velocity.x = -rigidBody.velocity.x;
			}
			else if (right >= 10) {
				sphere->centerPoint->x = 10 - sphere->radius;
				rigidBody.velocity.x = -rigidBody.velocity.x;
			}
			if (bottom < -10) {
				sphere->centerPoint->y = -10 + sphere->radius;
				rigidBody.velocity.t = -rigidBody.velocity.y;
			}
			else if (top > 10) {
				sphere->centerPoint->y = 10 - sphere->radius;
				rigidBody.velocity.y = -rigidBody.velocity.y;
			}
		}
		else if (!(left < -10 || right >= 10 || bottom < -10 || top > 10)) {
			rigidBody.repositioned = false;
		}

		auto& transform = coordinator->GetComponent<Transform>(entityA);
		// Forces
		auto const& gravity = coordinator->GetComponent<Gravity>(entityA);

		transform.position += rigidBody.velocity * dt * 10.f;

		rigidBody.velocity += gravity.force * dt;
	}
}