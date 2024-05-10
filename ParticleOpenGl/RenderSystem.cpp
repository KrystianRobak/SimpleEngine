#include "RenderSystem.h"

#include "Camera.h"
#include "Renderable.h"
#include "Transform.h"
#include "coordinator.h"
#include "Shader.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include "StaticMesh.h"
#include "Collision.h"



void RenderSystem::Init()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	coordinator->AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));

	shader = std::make_unique<Shader>("Default.vs", "Default.fs");

	mCamera = coordinator->CreateEntity();

	coordinator->AddComponent(
		mCamera,
		Transform{
			.position = glm::vec3(0.0f, 0.0f, 500.0f)
		});

	coordinator->AddComponent(
		mCamera,
		Camera{
			
		});
}

void RenderSystem::Update(float dt)
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();
	glBindVertexArray(mVao);


	auto& cameraTransform = coordinator->GetComponent<Transform>(mCamera);
	auto& camera = coordinator->GetComponent<Camera>(mCamera);

	glm::mat4 projection = glm::perspective(glm::radians(camera.fov), 800.f/600.f, 0.1f, 100.0f);
	shader->SetMat4("Projection", projection);

	// camera/view transformation
	glm::mat4 view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	shader->SetMat4("View", view);

	auto const& componentTypes = coordinator->GetComponentsTypes();

	for (auto const& entity : mEntities)
	{
		auto const& transform = coordinator->GetComponent<Transform>(entity);
		auto const& renderable = coordinator->GetComponent<Renderable>(entity);
		auto const& collider = coordinator->GetComponent<Collider>(entity);
		auto signature = coordinator->GetEntitySignature(entity);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, 20.f, transform.rotation);

		shader->SetMat4("Model", model);
		shader->SetVec3("Color", renderable.color);

		if (signature.test(coordinator->GetComponentType<StaticMesh>()))
		{
			auto& staticMesh = coordinator->GetComponent<StaticMesh>(entity);
			staticMesh.Draw(*shader.get());
		}
		
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), transform.scale);

		model = model * scaleMat;
		
		//collider.collider->DrawCollisionMesh();

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
	}

	glBindVertexArray(0);
}

void RenderSystem::WindowSizeListener(Event& event)
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	auto windowWidth = event.GetParam<unsigned int>(Events::Window::Resized::WIDTH);
	auto windowHeight = event.GetParam<unsigned int>(Events::Window::Resized::HEIGHT);

	auto& camera = coordinator->GetComponent<Camera>(mCamera);
	//camera.projectionTransform = Camera::MakeProjectionTransform(45.0f, 0.1f, 1000.0f, windowWidth, windowHeight);
}
