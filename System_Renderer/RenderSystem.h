#pragma once

#include "SystemInterface.h"
#include "Shader.h"
#include "Camera.h"
#include "coordinator.h"
#include <memory>


class Event;


class RenderSystem : public SystemInterface
{
public:
	void RenderBorder() {};

	void OnLightEntityAdded();
	void RecompileShader();
	
	virtual bool Initialize() override;
	virtual void Execute(float dt) override;
	virtual void Cleanup() override;

	virtual std::string GetName() const override;

	void SetupModelAndMesh(std::shared_ptr<Coordinator>& coordinator, const Entity& entity, Shader& ChangeShader);

	void BindCamera(Camera* CameraToUse)
	{
		CurrentlyUsedCamera = CameraToUse;
	}

private:
	void WindowSizeListener(Event& event);

	std::unique_ptr<Shader> shader;
	std::unique_ptr<Shader> LightShader;

	Camera* CurrentlyUsedCamera;

	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
};
