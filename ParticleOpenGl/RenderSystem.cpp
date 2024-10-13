#include "RenderSystem.h"

#include "Renderable.h"
#include "Transform.h"
#include "coordinator.h"
#include "Shader.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include "StaticMesh.h"
#include "Collision.h"
#include "LightSource.h"

void RenderSystem::OnLightEntityAdded()
{
	
}

void RenderSystem::RecompileShader()
{
	shader = std::make_unique<Shader>("Default.vs", "Default.fs");
	LightShader = std::make_unique<Shader>("shaders/LightSourceShader/LightSource.vs", "shaders/LightSourceShader/LightSource.fs");
}

void RenderSystem::Init()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	coordinator->AddEventListener(METHOD_LISTENER_ONE_PARAM(Events::Window::RESIZED, RenderSystem::WindowSizeListener));
	coordinator->AddEventListener(METHOD_LISTENER_NO_PARAM(Events::Application::RECOMPILE_SHADER, RenderSystem::RecompileShader));
	
	coordinator->AddEventListener(METHOD_LISTENER_NO_PARAM(Events::Application::LIGHT_ENTITY_ADDED, RenderSystem::OnLightEntityAdded));
	
	shader = std::make_unique<Shader>("Default.vs", "Default.fs");
	LightShader = std::make_unique<Shader>("shaders/LightSourceShader/LightSource.vs", "shaders/LightSourceShader/LightSource.fs");
	BindCamera(coordinator->GetCamera());
}

void RenderSystem::Update(float dt)
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	std::shared_ptr<ComponentManager> Manager = coordinator->GetComponentManager();

	std::shared_ptr<ComponentArray<Renderable>> RenderableArray = Manager->GetComponentArray<Renderable>();
	std::shared_ptr<ComponentArray<Transform>> TransformArray = Manager->GetComponentArray<Transform>();
	std::shared_ptr<ComponentArray<LightSource>> LightSourceArray = Manager->GetComponentArray<LightSource>();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*shader->Use();
	glBindVertexArray(mVao);

	glm::mat4 projection = glm::perspective(glm::radians(CurrentlyUsedCamera->fov), 800.f/600.f, 0.1f, 100.0f);
	

	glm::mat4 view = glm::lookAt(
		CurrentlyUsedCamera->CameraTransform.position,
		CurrentlyUsedCamera->CameraTransform.position + CurrentlyUsedCamera->cameraFront,
		CurrentlyUsedCamera->cameraUp);

	shader->SetMat4("Projection", projection);
	shader->SetMat4("View", view);
	shader->SetVec3("ViewPos", CurrentlyUsedCamera->CameraTransform.position);

	for (auto const& entity : mEntities)
	{
		auto const& transform = coordinator->GetComponent<Transform>(entity);
		auto const& renderable = coordinator->GetComponent<Renderable>(entity);
		auto signature = coordinator->GetEntitySignature(entity);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, 20.f, transform.rotation);

		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), transform.scale);

		model = model * scaleMat;

		shader->SetMat4("Model", model);

		if (signature.test(coordinator->GetComponentType<StaticMesh>()))
		{
			auto& staticMesh = coordinator->GetComponent<StaticMesh>(entity);
			staticMesh.Draw(*shader.get());
		}

		shader->SetVec3("ObjectColor", renderable.color);
		shader->SetVec3("LightColor", { 1,1,1 });

		shader->SetVec3("Material.Ambient", renderable.Ambient);
		shader->SetVec3("Material.Diffuse", renderable.Diffuse);
		shader->SetVec3("Material.Specular", renderable.Specular);
		shader->SetFloat("Material.Shininess", renderable.Shininess);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		LightShader->Use();
		LightShader->SetMat4("Projection", projection);
		LightShader->SetMat4("View", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}*/

	glBindVertexArray(0);
}

void RenderSystem::WindowSizeListener(Event& event)
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	auto windowWidth = event.GetParam<unsigned int>(Events::Window::Resized::WIDTH);
	auto windowHeight = event.GetParam<unsigned int>(Events::Window::Resized::HEIGHT);

	Camera* camera = coordinator->GetCamera();
	//camera.projectionTransform = Camera::MakeProjectionTransform(45.0f, 0.1f, 1000.0f, windowWidth, windowHeight);
	

}

