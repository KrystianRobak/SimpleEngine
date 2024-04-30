#include "RenderSystem.h"

#include "Camera.h"
#include "Renderable.h"
#include "Transform.h"
#include "coordinator.h"
#include "Shader.h"

#include <../gtc/matrix_transform.hpp>
#include <../gtc/type_ptr.hpp>
#include <cmath>
#include "StaticMesh.h"



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

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	float normals[] = {
		// Front face
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// Back face
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Left face
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		// Right face
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// Bottom face
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		// Top face
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// Vertices
	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glGenBuffers(1, &mVboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
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

	for (auto const& entity : mEntities)
	{
		auto const& transform = coordinator->GetComponent<Transform>(entity);
		auto const& renderable = coordinator->GetComponent<Renderable>(entity);

		auto signature = coordinator->GetEntitySignature(entity);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, 20.f, transform.rotation);

		if (signature.test(coordinator->GetComponentType<StaticMesh>()))
		{
			auto& staticMesh = coordinator->GetComponent<StaticMesh>(entity);
			staticMesh.Draw(*shader.get());
		}
		else
		{
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), transform.scale);

			model = model * scaleMat;

			shader->SetMat4("Model", model);
			shader->SetVec3("Color", renderable.color);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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
