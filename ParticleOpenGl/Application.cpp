#include "Application.h"
#include "StaticMesh.h"
#include "thread"

#include "Types.h"

void Application::Init()
{
	Coordinator = Coordinator::GetCoordinator();

	Coordinator->AddEventListener(METHOD_LISTENER_NO_PARAM(Events::Application::TOGGLE, Application::ToggleApplication));

	Coordinator->RegisterComponent<Camera>();
	Coordinator->RegisterComponent<Gravity>();
	Coordinator->RegisterComponent<Player>();
	Coordinator->RegisterComponent<Renderable>();
	Coordinator->RegisterComponent<RigidBody>();
	Coordinator->RegisterComponent<Thrust>();
	Coordinator->RegisterComponent<Transform>();
	Coordinator->RegisterComponent<Collider>();
	Coordinator->RegisterComponent<StaticMesh>();
	Coordinator->RegisterComponent<LightSource>();

	auto physicsSystem = Coordinator->RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(Coordinator->GetComponentType<Gravity>());
		signature.set(Coordinator->GetComponentType<RigidBody>());
		signature.set(Coordinator->GetComponentType<Transform>());
		signature.set(Coordinator->GetComponentType<Collider>());
		Coordinator->SetSystemSignature<PhysicsSystem>(signature);
	}

	physicsSystem->Init();

	auto cameraControlSystem = Coordinator->RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(Coordinator->GetComponentType<Camera>());
		signature.set(Coordinator->GetComponentType<Transform>());
		Coordinator->SetSystemSignature<CameraControlSystem>(signature);
	}

	cameraControlSystem->Init();


	auto playerControlSystem = Coordinator->RegisterSystem<PlayerControlSystem>();
	{
		Signature signature;
		signature.set(Coordinator->GetComponentType<Player>());
		signature.set(Coordinator->GetComponentType<Transform>());
		Coordinator->SetSystemSignature<PlayerControlSystem>(signature);
	}

	playerControlSystem->Init();


	auto renderSystem = Coordinator->RegisterSystem<RenderSystem>();
	{
		Signature signature;

		Coordinator->SetSystemSignature<RenderSystem>(signature);
	}

	running = false;
	renderSystem->Init();
}

void Application::Update()
{
	auto playerControlSystem = Coordinator->GetSystem<PlayerControlSystem>();
	auto cameraControlSystem = Coordinator->GetSystem<CameraControlSystem>();
	auto physicsSystem = Coordinator->GetSystem<PhysicsSystem>();

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
		//std::this_thread::sleep_for(std::chrono::duration<float>(sleepDuration));
	}


	frameEndTime = std::chrono::high_resolution_clock::now();
	dt = std::chrono::duration<float>(frameEndTime - frameStartTime).count();
}

void Application::Render()
{
	auto renderSystem = Coordinator->GetSystem<RenderSystem>();

	renderSystem->Update(dt);
}


void Application::RenderEntitiesUI()
{

}
