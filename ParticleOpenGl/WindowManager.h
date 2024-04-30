#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <bitset>
#include <string>


class WindowManager
{
public:
	void Init(
		std::string const& windowTitle, unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPositionX, unsigned int windowPositionY);

	void Update();
	GLFWwindow* GetWindow()
	{
		return this->mWindow;
	}

	void ProcessEvents();

	void Shutdown();

private:
	GLFWwindow* mWindow;

	std::bitset<8> mButtons;
};