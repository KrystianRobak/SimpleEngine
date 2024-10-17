#pragma once

#include "SystemInterface.h"
#include "Camera.h"

class Event;


class CameraControlSystem : public SystemInterface
{
public:
	void Init();

	void Update(float dt);

	void BindCamera(Camera* NewCamera)
	{	
		ControlledCamera = NewCamera;
	}

private:
	int mButtons;

	void InputListener(Event& event);
	Camera* ControlledCamera;
};
