#include "CameraControlSystem.h"

#include "Transform.h"
#include "coordinator.h"




void CameraControlSystem::Init()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();
	coordinator->AddEventListener(METHOD_LISTENER(Events::Window::INPUT, CameraControlSystem::InputListener));
}

void CameraControlSystem::Update(float dt)
{
	Coordinator* coordinator = Coordinator::GetCoordinator();
	for (auto& entity : mEntities)
	{
		auto& transform = coordinator->GetComponent<Transform>(entity);

		float speed = 20.0f;


		if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
		{
			transform.position.z -= (dt * speed);
		}

		else if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
		{
			transform.position.z += (dt * speed);
		}


		if (mButtons.test(static_cast<std::size_t>(InputButtons::Q)))
		{
			transform.position.y += (dt * speed);
		}

		else if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))
		{
			transform.position.y -= (dt * speed);
		}


		if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
		{
			transform.position.x -= (dt * speed);
		}

		else if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
		{
			transform.position.x += (dt * speed);
		}
	}
}

void CameraControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}

