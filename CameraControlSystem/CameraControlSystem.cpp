#include "CameraControlSystem.h"


void CameraControlSystem::Init()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
	coordinator->AddEventListener(METHOD_LISTENER_ONE_PARAM(Events::Window::INPUT, CameraControlSystem::InputListener));

	//BindCamera(coordinator->GetCamera());
}

void CameraControlSystem::Update(float dt)
{
	float speed = 0.25f;

	if (mButtons == 'W')
	{
		ControlledCamera->CameraTransform.position.z -= speed;//(dt * speed);
	}
	if (mButtons == 'S')
	{
		ControlledCamera->CameraTransform.position.z += speed;//(dt * speed);
	}
	if (mButtons == 'A')
	{
		ControlledCamera->CameraTransform.position.x -= speed;//(dt * speed);
	}
	if (mButtons == 'D')
	{
		ControlledCamera->CameraTransform.position.x += speed;//(dt * speed);
	}
	if (mButtons == 'Q')
	{
		ControlledCamera->CameraTransform.position.y += speed;//(dt * speed);
	}
	if (mButtons == 'E')
	{
		ControlledCamera->CameraTransform.position.y -= speed;//(dt * speed);
	}

	//else if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))

	mButtons = 0;
}

void CameraControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<int>("InputKey");
}

