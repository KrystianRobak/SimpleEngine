#include "WindowManager.h"

#include <bitset>
#include <iostream>


// TODO: Return error to caller
void WindowManager::Init(
	std::string const& windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int windowPositionX,
	unsigned int windowPositionY)
{
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}

	// Create a windowed mode window and its OpenGL context
	
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	if (!mWindow) {
		glfwTerminate();
	}

	// Make the window's context current
	glfwMakeContextCurrent(mWindow);
	glewExperimental = true;
	glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	// Initialize GLEW

	if (glewInit() != GLEW_OK) {
	}

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 255.0f, 255.4f, 0.0f);
}


void WindowManager::Update()
{
	glfwSwapBuffers(mWindow);
}


void WindowManager::Shutdown()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}