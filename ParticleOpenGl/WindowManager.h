#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <utility>

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
	static std::pair<float, float> GetMouseLocation() { return mouseLocation; };
private:
	static GLFWwindow* window;
	static bool bIsFocused;

	static std::pair<float, float> mouseLocation;
	static int width;
	static int height;
};

