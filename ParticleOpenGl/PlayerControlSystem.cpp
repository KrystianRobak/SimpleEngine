#include "PlayerControlSystem.h"

#include "Player.h"
#include "Thrust.h"
#include "Transform.h"
#include "coordinator.h"


void PlayerControlSystem::Init()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();
	coordinator->AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerControlSystem::InputListener));
}

void PlayerControlSystem::Update(float dt)
{
	//for (auto& entity : mEntities)
	//{
	//	auto& transform = coordinator->Get<Transform>(entity);


	//	if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
	//	{
	//		transform.position.z += (dt * 10.0f);
	//	}

	//	else if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
	//	{
	//		transform.position.z -= (dt * 10.0f);
	//	}


	//	if (mButtons.test(static_cast<std::size_t>(InputButtons::Q)))
	//	{
	//		transform.position.y += (dt * 10.0f);
	//	}

	//	else if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))
	//	{
	//		transform.position.y -= (dt * 10.0f);
	//	}


	//	if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
	//	{
	//		transform.position.x += (dt * 10.0f);
	//	}

	//	else if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
	//	{
	//		transform.position.x -= (dt * 10.0f);
	//	}
	//}
}

void PlayerControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}
