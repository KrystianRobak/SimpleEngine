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
#include "Window.h"
#include "SystemInitializer.h"


class Application
{
private:
	void Render();

	void LoadSystems();

	void ToggleApplication()
	{
		this->running = !this->running;
	}

public:

	void Init();
	void Update();

	bool IsRunning()
	{
		return running;
	}

private:
	float dt = 0.0f;
	bool running;
	std::shared_ptr<Coordinator> Coordinator;
	std::shared_ptr<Window> WindowManager;
	std::shared_ptr<SystemInitializer> Initializer;
};

