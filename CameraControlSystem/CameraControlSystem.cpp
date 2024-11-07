#define SYSTEMINTERFACE_EXPORTS
#include "CameraControlSystem.h"


bool CameraControlSystem::Initialize()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
	coordinator->AddEventListener(METHOD_LISTENER_ONE_PARAM(Events::Window::INPUT, CameraControlSystem::InputListener));

	return true;
	//BindCamera(coordinator->GetCamera());
}

void CameraControlSystem::Execute(float dt)
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

void CameraControlSystem::Cleanup()
{
}

std::string CameraControlSystem::GetName() const
{
	return "Camera Control System";
}

void CameraControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<int>("InputKey");
}

extern "C" {

	SYSTEMINTERFACE_API SystemInterface* CreatePlugin()
	{
		return new CameraControlSystem();
	}

	SYSTEMINTERFACE_API void DestroyPlugin(SystemInterface* System)
	{
		delete System;
	}

}