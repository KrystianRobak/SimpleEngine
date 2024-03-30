#pragma once
#include "WindowManager.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include <../glm/gtc/matrix_transform.hpp>

class InputManager
{
public:
	InputManager(GLFWwindow* window)
	{
		this->window = window;
	};

	void ComputeMatricesFromInput();

private:
	GLFWwindow* window;

};

