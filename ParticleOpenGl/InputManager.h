#pragma once
#include "WindowManager.h"
#include <GLFW/glfw3.h>
#include <../glm.hpp>
#include <../gtc/matrix_transform.hpp>
#include "Camera.h"

class InputManager
{
public:
	InputManager(GLFWwindow* window)
	{
		this->window = window;
	};

	void ComputeMatricesFromInput();

	void ProcessInput(float deltaTime);

private:
	GLFWwindow* window;
	Camera* camera;
	bool cursorTogglePressed = false;
};

