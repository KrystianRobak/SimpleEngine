#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define INITIAL_WIDTH 1024
#define INITIAL_HEIGHT 768

class WindowManager
{
private:
	WindowManager() {
	}

public:
	static GLFWwindow* GetWindow();
	static void focusCallback(GLFWwindow* window, int focused);
	static bool IsFocused() { return bIsFocused; };
	static int GetWidth() { return width; };
	static int GetHeight() { return height; };
private:
	static GLFWwindow* window;
	static bool bIsFocused;

	static int width;
	static int height;
};

