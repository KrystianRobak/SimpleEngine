#include "Application.h"
#include "StaticMesh.h"
#include "thread"

#include "Types.h"

void Application::Init()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	coordinator->AddEventListener(METHOD_LISTENER_NO_PARAM(Events::Application::TOGGLE, Application::ToggleApplication));

	coordinator->RegisterComponent<Camera>();	
	coordinator->RegisterComponent<Gravity>();
	coordinator->RegisterComponent<Player>();
	coordinator->RegisterComponent<Renderable>();
	coordinator->RegisterComponent<RigidBody>();
	coordinator->RegisterComponent<Thrust>();
	coordinator->RegisterComponent<Transform>();
	coordinator->RegisterComponent<Collider>();
	coordinator->RegisterComponent<StaticMesh>();


	auto physicsSystem = coordinator->RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(coordinator->GetComponentType<Gravity>());
		signature.set(coordinator->GetComponentType<RigidBody>());
		signature.set(coordinator->GetComponentType<Transform>());
		signature.set(coordinator->GetComponentType<Collider>());
		coordinator->SetSystemSignature<PhysicsSystem>(signature);
	}

	physicsSystem->Init();

	auto cameraControlSystem = coordinator->RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(coordinator->GetComponentType<Camera>());
		signature.set(coordinator->GetComponentType<Transform>());
		coordinator->SetSystemSignature<CameraControlSystem>(signature);
	}

	cameraControlSystem->Init();


	auto playerControlSystem = coordinator->RegisterSystem<PlayerControlSystem>();
	{
		Signature signature;
		signature.set(coordinator->GetComponentType<Player>());
		signature.set(coordinator->GetComponentType<Transform>());
		coordinator->SetSystemSignature<PlayerControlSystem>(signature);
	}

	playerControlSystem->Init();


	auto renderSystem = coordinator->RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(coordinator->GetComponentType<Renderable>());
		signature.set(coordinator->GetComponentType<Transform>());
		signature.set(coordinator->GetComponentType<Collider>());

		coordinator->SetSystemSignature<RenderSystem>(signature);
	}

	running = false;
	renderSystem->Init();
}

void Application::Update()
{
		std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

		auto playerControlSystem = coordinator->GetSystem<PlayerControlSystem>();
		auto cameraControlSystem = coordinator->GetSystem<CameraControlSystem>();
		auto physicsSystem = coordinator->GetSystem<PhysicsSystem>();

		const float targetFrameDuration = 1.0f / 165.0f; // 165 FPS
		auto frameStartTime = std::chrono::high_resolution_clock::now();

		playerControlSystem->Update(dt);
		cameraControlSystem->Update(dt);
		physicsSystem->Update(dt);

		auto frameEndTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float>(frameEndTime - frameStartTime).count();

		float sleepDuration = targetFrameDuration - dt;
		if (sleepDuration > 0)
		{
			std::this_thread::sleep_for(std::chrono::duration<float>(sleepDuration));
		}


		frameEndTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float>(frameEndTime - frameStartTime).count();
}

void Application::Render()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	auto renderSystem = coordinator->GetSystem<RenderSystem>();

	renderSystem->Update(dt);
}


void Application::RenderEntitiesUI()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();
}
