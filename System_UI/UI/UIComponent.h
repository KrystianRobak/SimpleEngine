#pragma once

#include "../ImGuiCompiled/imgui.h"
#include "../ImGuiCompiled/imgui_impl_glfw.h"
#include "../ImGuiCompiled/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <string>

class UIComponent
{
public:
	virtual void Render() = 0;
};