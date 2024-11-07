#pragma once

#include "SystemInterface.h"
#include "Transform.h"
#include "coordinator.h"
#include "Camera.h"

class Event;


class CameraControlSystem : public SystemInterface
{
public:

	virtual ~CameraControlSystem() {}

	virtual bool Initialize() override;
	virtual void Execute(float dt) override;
	virtual void Cleanup() override;

	virtual std::string GetName() const override;

	void BindCamera(Camera* NewCamera)
	{	
		ControlledCamera = NewCamera;
	}

private:
	int mButtons;

	void InputListener(Event& event);
	Camera* ControlledCamera;
};
