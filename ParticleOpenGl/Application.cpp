#include "Application.h"
#include "StaticMesh.h"
#include "thread"

#include "Types.h"

float DtTimer()
{
	const float targetFrameDuration = 1.0f / 165.0f; // 165 FPS
	auto frameStartTime = std::chrono::high_resolution_clock::now();

	auto frameEndTime = std::chrono::high_resolution_clock::now();
	float dt = std::chrono::duration<float>(frameEndTime - frameStartTime).count();

	float sleepDuration = targetFrameDuration - dt;
	if (sleepDuration > 0)
	{
		//std::this_thread::sleep_for(std::chrono::duration<float>(sleepDuration));
	}

	frameEndTime = std::chrono::high_resolution_clock::now();
	dt = std::chrono::duration<float>(frameEndTime - frameStartTime).count();
	return dt;
}


void Application::Init()
{
	Coordinator = Coordinator::GetCoordinator();

	Coordinator->AddEventListener(METHOD_LISTENER_NO_PARAM(Events::Application::TOGGLE, Application::ToggleApplication));
}

void Application::Update()
{
	dt = DtTimer();
	
}

void Application::Render()
{
}


void Application::RenderEntitiesUI()
{

}


//Coordinator->RegisterComponent<Camera>();
//Coordinator->RegisterComponent<Gravity>();
//Coordinator->RegisterComponent<Player>();
//Coordinator->RegisterComponent<Renderable>();
//Coordinator->RegisterComponent<RigidBody>();
//Coordinator->RegisterComponent<Thrust>();
//Coordinator->RegisterComponent<Transform>();
//Coordinator->RegisterComponent<Collider>();
//Coordinator->RegisterComponent<StaticMesh>();
//Coordinator->RegisterComponent<LightSource>();
//
//auto physicsSystem = Coordinator->RegisterSystem<PhysicsSystem>();
//{
//	Signature signature;
//	signature.set(Coordinator->GetComponentType<Gravity>());
//	signature.set(Coordinator->GetComponentType<RigidBody>());
//	signature.set(Coordinator->GetComponentType<Transform>());
//	Coordinator->SetSystemSignature<PhysicsSystem>(signature);
//}
//
//physicsSystem->Init();
//
//auto cameraControlSystem = Coordinator->RegisterSystem<CameraControlSystem>();
//{
//	Signature signature;
//	signature.set(Coordinator->GetComponentType<Camera>());
//	signature.set(Coordinator->GetComponentType<Transform>());
//	Coordinator->SetSystemSignature<CameraControlSystem>(signature);
//}
//
//cameraControlSystem->Init();
//
//
//
//auto renderSystem = Coordinator->RegisterSystem<RenderSystem>();
//{
//	Signature signature;
//
//	Coordinator->SetSystemSignature<RenderSystem>(signature);
//}
//
//renderSystem->Init();
//
//auto uiSystem = Coordinator->RegisterSystem<UiSystem>();
//{
//	Signature signature;
//
//	Coordinator->SetSystemSignature<UiSystem>(signature);
//}
//
//uiSystem->Initialize();
//
//running = false;