#pragma once

#include "System.h"
#include "Shader.h"
#include "Camera.h"
#include <memory>


class Event;


class RenderSystem : public System
{
public:
	void RenderBorder();
	void Init();

	void OnLightEntityAdded();
	void RecompileShader();
	
	
	void Update(float dt);

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
