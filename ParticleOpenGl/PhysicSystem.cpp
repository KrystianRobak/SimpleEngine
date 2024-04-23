#include "PhysicSystem.h"
#include "PhysicComponent.h"

void PhysicSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		auto& rigidBody = coordinatorPtr->GetComponent<RigidBody>(entity);
		auto& transform = coordinatorPtr->GetComponent<Transform>(entity);
		auto const& gravity = coordinatorPtr->GetComponent<Gravity>(entity);

		transform.position += rigidBody.velocity * dt;

		rigidBody.velocity += gravity.force * dt;
	}

}
