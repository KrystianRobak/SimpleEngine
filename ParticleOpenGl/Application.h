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

#include "coordinator.h"

#include "CameraControlSystem.h"
#include "PhysicsSystem.h"
#include "PlayerControlSystem.h"
#include "RenderSystem.h"

#include "WindowManager.h"
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
};

