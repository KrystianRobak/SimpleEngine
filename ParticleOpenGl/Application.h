#pragma once

#include "Gravity.h"
#include "RigidBody.h"
#include "Renderable.h"
#include "Thrust.h"
#include "Transform.h"
#include "Collision.h"
#include "Camera.h"
#include "Player.h"
#include "Thrust.h"
#include "LightSource.h"

#include "coordinator.h"

#include "CameraControlSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "UiSystem.h"

#include <chrono>
#include <random>


class Application
{
public:
	void Init();
	void Update();
	void Render();

	void RenderEntitiesUI();

	void ToggleApplication()
	{
		this->running = !this->running;
	}

	bool IsRunning()
	{
		return running;
	}
private:
	float dt = 0.0f;
	bool running;
	std::shared_ptr<Coordinator> Coordinator;
};

