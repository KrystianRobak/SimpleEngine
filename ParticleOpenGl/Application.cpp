#include "Application.h"
#include "StaticMesh.h"

void Application::Init()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

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

	renderSystem->Init();

	/*std::vector<Entity> entities(MAX_ENTITIES - 1);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-10.0f, 10.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	for (auto& entity : entities)
	{
		entity = coordinator->CreateEntity();
		std::cout << entity << std::endl;
		coordinator->AddComponent(entity, Player{});

		coordinator->AddComponent<Gravity>(
			entity,
			{ glm::vec3(0.0f, -3, 0.0f) });

		coordinator->AddComponent(
			entity,
			RigidBody{
				.velocity = glm::vec3(0.0f, 0.0f, 0.0f),
				.acceleration = glm::vec3(0.0f, 0.0f, 0.0f)
			});

		coordinator->AddComponent(
			entity,
			Transform{
				.position = glm::vec3(randPosition(generator), randPosition(generator), -30),
				.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
				.scale = glm::vec3(scale, scale, scale)
			});

		coordinator->AddComponent(
			entity,
			Renderable{
				.color = glm::vec4(randColor(generator), randColor(generator), randColor(generator), 1)
			});
	}*/
}

void Application::Update()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	auto playerControlSystem = coordinator->GetSystem<PlayerControlSystem>();
	auto cameraControlSystem = coordinator->GetSystem<CameraControlSystem>();
	auto physicsSystem = coordinator->GetSystem<PhysicsSystem>();


	auto startTime = std::chrono::high_resolution_clock::now();

	playerControlSystem->Update(dt);

	cameraControlSystem->Update(dt);

	physicsSystem->Update(dt);


	auto stopTime = std::chrono::high_resolution_clock::now();

	dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();

}

void Application::Render()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	auto renderSystem = coordinator->GetSystem<RenderSystem>();

	renderSystem->Update(dt);
}


void Application::RenderEntitiesUI()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();



}
