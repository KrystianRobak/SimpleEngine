#pragma once

#include "System.h"
#include "Shader.h"
#include <memory>


class Event;


class RenderSystem : public System
{
public:
	void RenderBorder();
	void Init();

	void Update(float dt);

private:
	void WindowSizeListener(Event& event);

	std::unique_ptr<Shader> shader;

	Entity mCamera;

	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
};
