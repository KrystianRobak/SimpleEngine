#include "Application.h"

#include "PhysicComponent.h"
#include "PhysicSystem.h"
#include <random>


Application::Application(const std::string& app_name)
{
    window = std::make_unique<Window>();
    window->init(1024, 720, app_name);

}

void Application::Init()
{
    coordinator.Init();

    coordinator.RegisterComponent<Gravity>();
    coordinator.RegisterComponent<RigidBody>();
    coordinator.RegisterComponent<Transform>();

    auto physicSystem = coordinator.RegisterSystem<PhysicSystem>();
	physicSystem->Bind(coordinator);

    Signature signature;
    signature.set(coordinator.GetComponentType<Gravity>());
    signature.set(coordinator.GetComponentType<RigidBody>());
    signature.set(coordinator.GetComponentType<Transform>());
    coordinator.SetSystemSignature<PhysicSystem>(signature);

    std::vector<Entity> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);


	for (auto& entity : entities)
	{
		entity = coordinator.CreateEntity();

		coordinator.AddComponent(
			entity,
			Gravity{ glm::vec3(0.0f, randGravity(generator), 0.0f) });

		coordinator.AddComponent(
			entity,
			RigidBody{
				.velocity = glm::vec3(0.0f, 0.0f, 0.0f),
				.acceleration = glm::vec3(0.0f, 0.0f, 0.0f)
			});

		coordinator.AddComponent(
			entity,
			Transform{
				.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
				.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
				.scale = glm::vec3(scale, scale, scale)
			});
	}


}

void Application::loop()
{
	while (window->is_running())
	{
		window->Render();
		GameLoop();
	}
}


void Application::GameLoop()
{
	auto startTime = std::chrono::high_resolution_clock::now();
	
	coordinator.Proceed(dt);

	auto stopTime = std::chrono::high_resolution_clock::now();

	dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();

}
