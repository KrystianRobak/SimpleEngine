#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm.hpp>

struct Renderable
{
	glm::vec4 color;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string entityStr = std::to_string(entity);

        std::string colorLabel = "Color##" + entityStr;
        ImGui::ColorPicker4(colorLabel.c_str(), &color[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
    }
};
